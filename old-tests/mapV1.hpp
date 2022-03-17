/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 06-03-2022  by  `-'                        `-'                  */
/*   Updated: 16-03-2022 14:41 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pairs.hpp"
#include "iterators.hpp"
#include "RBT.hpp"
#include "MapIterator.hpp"

#include <memory>
#include <functional>

namespace ft
{

	template < class Key,                                     			// map::key_type
			   class T,                                       			// map::mapped_type
			   class Compare = std::less<Key>,                   		// map::key_compare
			   class Alloc = std::allocator<ft::pair<Key,T> >	>	// map::allocator_type
	class map
	{
		private:
			typedef RBTree<pair<Key, T>, Compare, Alloc>	tree_type;
			typedef typename tree_type::node_pointer		node_pointer;
			typedef typename tree_type::node				node_type;
			
		public:
			//template <class Map>
			//class MapIterator;

			struct ValueCompare;

			typedef Key								key_type;
			typedef T								mapped_type;
			typedef pair<key_type, mapped_type>		value_type;
			typedef Compare							key_compare;
			typedef ValueCompare					value_compare; /* Returns an object that can be used to compare 2 elements, (pair element not key) */
			typedef Alloc							allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
		
			/* When dereferencing iterator we access a std::pair<Key, T>, just like vector access T */
			typedef MapIterator<value_type, node_type, false>	iterator;
			typedef MapIterator<value_type, node_type, true>	const_iterator;
			
			//typedef MapIterator< map<Key, T, Compare, Alloc> >				iterator;
			//typedef MapIterator< map<const Key, const T, Compare, Alloc> >	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			/* Identical to iterator_traits<iterator>::size_type/difference_type */
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type;

		private:
			key_compare									_comp;
			allocator_type								_alloc;	
			RBTree<value_type, value_compare, Alloc>	_tree;

		public:
		
			// Default constructor / empty
			explicit map(const key_compare& comp = key_compare(),
			              const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) { }

			// Range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			     const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc)
			{
				while (first != last)
				{
					this->_tree.insert(*first);
					++first;
				}
			}

			// Copy constructor
			map(const map& x)
			{
				this->_alloc = x._alloc;
				this->_comp = x._comp;

				for (map::iterator it = x.begin(); it != x.end(); ++it)
					this->_tree.insert(*it);
			}
	   
			/* Iterators */
			iterator		begin()
			{
				if (this->size() == 0)
					return (this->end());

				return (iterator(this->_tree.first()));
			}

			const_iterator	begin() const
			{
				if (this->size() == 0)
					return (this->end());
				return (iterator(this->_tree.first()));
			}

			iterator		end() { return (iterator(/*this->_tree.end()*/NULL)); }
			const_iterator	end() const { return (const_iterator(/*this->_tree.end()*/NULL)); }

			reverse_iterator		rbegin() { return (ft::reverse_iterator<iterator>(this->end())); }
			const_reverse_iterator	rbegin() const { return (ft::reverse_iterator<const_iterator>(this->end())); }

			reverse_iterator		rend() { return (ft::reverse_iterator<iterator>(this->begin())); }
			const_reverse_iterator	rend() const { return (ft::reverse_iterator<const_iterator>(this->begin())); }
	
			/* Capacity */
			bool empty() const { return (this->_tree.size() == 0); }
			size_type size() const { return (this->_tree.size()); }
			size_type max_size() const { return (this->_alloc.max_size()); }


			/* Modifiers */
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				node_pointer alreadyExists = this->_tree.search(val);

				if (alreadyExists != NULL) /* Value already in tree */
					return (ft::make_pair(iterator(alreadyExists), false));
				
				this->_tree.insert(val);
				return (ft::make_pair(iterator(this->_tree.search(val)), true));
			}

			/* Insert as close to position as possible (to optimize insertion we give hint) \.
			   Since we don't want our container to be fully optimized, just call insert coz im lazy */
			iterator insert(iterator position, const value_type& val)
			{
				(void) position;
				
				return (this->insert(val).first);
			}

			template <class InputIterator>
 			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->_tree.insert(*first++);
			}

			void erase(iterator position)
			{
				this->_tree.remove(*position);
			}

			size_type erase(const key_type& k)
			{
				size_type return_val = 0;
				value_type  tmp_pair(k, mapped_type()); /* Create a temporary to make a pair, easier to find */

				if (this->_tree.search(tmp_pair) != NULL)
				{
					this->_tree.remove(tmp_pair);
					return_val = 1;
				}
				return (return_val);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					this->_tree.remove(*first++);
			}

			void swap(map& x)
			{
				node_pointer tmp_tree = this->_tree;

				this->_tree = x._tree;
				x._tree = tmp_tree;
			}

			void clear()
			{
				this->_tree.clear();
			}

			/* Element accesses */
			/* Inserts the element, .first return the iterator (which points to the value
				   no matter if it was added or was already there), then retrieves the value
				   
			Will basically return a value == k if k was inserted, and != k if it was already present */
			mapped_type& operator[](const key_type& k)
			{
				return (*((this->insert(make_pair(k, mapped_type()))).first)).second;
			}

			/* Observers */
			key_compare key_comp() const { return (key_comp()); }

			/* Compare using value (pair) instead of key */
			struct ValueCompare
			{
				/* Work like: 'ValueCompare comp; comp(pouet, pouet) == true' */
				bool operator()(value_type lhs, value_type rhs)
				{
					Compare comp;
					return (comp(lhs.first, rhs.first));
				}
			};

			value_compare value_comp() const { return (this->_comp); }

			/* Operations */
			iterator find(const key_type& k)
			{
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == NULL)
					return (this->end());
				
				return (iterator(value));
			}

			const_iterator find(const key_type& k) const
			{
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == NULL)
					return (this->end());
				
				return (const_iterator(value));
			}

			/* Basically returns either 1 or 0 in map, but not in containers like multiset, which is the same as map without unique */
			size_type count(const key_type& k) const
			{
				value_type tmp_pair(k, mapped_type());

				if (this->_tree.search(tmp_pair) != NULL)
					return (1);
				return (0);
			}

			/* Returns first node (in-order) considered not to be before k (equivalent or goes after)
			   (which most likely is k if it exists, otherwise the nearest upper value) */
			iterator lower_bound(const key_type& k)
			{
				node_pointer curr = this->_tree.first();
				
				while (curr != NULL && _comp(curr->data->first, k))
					curr = tree_type::inorderNext(curr);
				
				if (curr == NULL)
					return (this->end());

				return (iterator(curr));
			}

			const_iterator lower_bound(const key_type& k) const
			{
				node_pointer curr = this->_tree.first();
				
				while (curr != NULL && _comp(curr->data->first, k))
					curr = tree_type::inorderNext(curr);
				
				if (curr == NULL)
					return (this->end());

				return (const_iterator(curr));
			}

			iterator upper_bound(const key_type& k)
			{
				node_pointer curr = this->_tree.first();

				// value > key
				
				// 2 > 2
				// 2 > 1
				// !1 < 2

				// value > key == key !< value && (key != value)
				while (curr != NULL && 
				!_comp(k, curr->data->first) &&
				(!_comp(k, curr->data->first) && !_comp(curr->data->first, k)))
					curr = tree_type::inorderNext(curr);
				
				if (curr == NULL)
					return (iterator(this->end()));
				return (iterator(curr));
			}

			const_iterator upper_bound(const key_type& k) const
			{
				node_pointer curr = this->_tree.first();

				while (curr != NULL && 
				!_comp(k, curr->data->first) &&
				(!_comp(k, curr->data->first) && !_comp(curr->data->first, k)))
					curr = tree_type::inorderNext(curr);
				
				if (curr == NULL)
					return (const_iterator(this->end()));
				return (const_iterator(curr));
			}

			/* Returns the bound of a range that includes all the elements which have a key equivalent to k
			   since it's a map and has unique key, the range will contain at most 1 value */
			pair<iterator,iterator> equal_range(const key_type& k)
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			/* Allocator */
			allocator_type get_allocator() const { return (Alloc()); }

			// template <typename Node>
			// class MapIterator
			// {
			// 	private:
			// 		typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>	iterator;
			// 		typedef typename RBTree<value_type, Compare>::node_pointer					node_pointer;
			// 		typedef RBTree<value_type, Compare, Alloc>									tree;

			// 		/* end.left is root, end.right is end */
			// 		static bool isEndNode(node_pointer node)
			// 		{
			// 			return (node == NULL || node->right == node);
			// 		}

			// 		node_pointer findRoot(node_pointer node)
			// 		{
			// 			if (node == NULL)
			// 				return (NULL);

			// 			if (isEndNode(node))
			// 				return (node->left);

			// 			if (node->parent == NULL) /* Node IS the root */
			// 				return (node);

			// 			while (node->parent != NULL)
			// 				node = node->parent;
						
			// 			return (node);
			// 		}

			// 		node_pointer findLast(node_pointer root)
			// 		{
			// 			if (root == NULL)
			// 				return (NULL);


			// 			while (tree::inorderNext(root) != NULL)
			// 				root = tree::inorderNext(root);

			// 			return (root);
			// 		}


			// 	public:
			// 		typedef typename iterator::iterator_category	iterator_category;
			// 		typedef typename iterator::value_type			value_type;
			// 		typedef typename iterator::reference			reference;
			// 		typedef typename iterator::pointer				pointer;

			// 		typedef ptrdiff_t	difference_type;
			// 		typedef size_t		size_type;

			// 		MapIterator(node_pointer node) : _node(node), _root(this->findRoot(_node)) { }
			// 		MapIterator() : _node(NULL), _root(this->findRoot(_node)) { }
			// 		MapIterator(const MapIterator& m) : _node(m._node), _root(this->findRoot(_node)) { }
			// 		~MapIterator() { }

			// 		MapIterator& operator=(const MapIterator& m)
			// 		{
			// 			this->_node = m._node;
			// 			return (*this);
			// 		}

			// 		reference operator*() { return (*this->_node->data); }

			// 		const_reference operator*() const { return (*this->_node->data); }

			// 		pointer operator->() { return (this->_node->data); }

			// 		/* If we are past-the end, save the last element and set to null, then if we want to go back, node = last */
			// 		MapIterator& operator++()
			// 		{
			// 			this->_node = tree::inorderNext(this->_node);
			// 			return (*this);
			// 		}

			// 		MapIterator operator++(int)
			// 		{
			// 			MapIterator tmp = *this; /* Calls copy constructor, smart C++ */
			// 			++(*this);
			// 			return (tmp);
			// 		}

			// 		MapIterator& operator--()
			// 		{
			// 			if (this->_node == NULL)
			// 				this->_node = this->findLast(this->_root);
			// 			else
			// 				this->_node = tree::inorderPrev(this->_node);
			// 			return (*this);
			// 		}

			// 		MapIterator operator--(int)
			// 		{
			// 			MapIterator tmp = *this;
			// 			--(*this);
			// 			return (tmp);
			// 		}

			// 		/* Check if either both nodes are equal, or if it's on the end node */
			// 		friend bool operator==(const MapIterator& lhs, const MapIterator& rhs)
			// 		{
			// 			if (isEndNode(lhs._node) || isEndNode(rhs._node))
			// 				return (isEndNode(lhs._node) && isEndNode(rhs._node));

			// 			return (lhs._node == rhs._node);
			// 		}
			// 		friend bool operator!=(const MapIterator& lhs, const MapIterator& rhs) { return (!(lhs == rhs)); }

			// 	private:
			// 		node_pointer _node;
			// 		node_pointer _root;
			// };


	};

}

#endif