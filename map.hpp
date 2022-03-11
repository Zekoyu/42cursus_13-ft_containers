/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 06-03-2022  by  `-'                        `-'                  */
/*   Updated: 11-03-2022 14:54 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pairs.hpp"
#include "iterators.hpp"
#include "RBT.hpp"

#include <memory>
#include <functional>

namespace ft
{

	template < class Key,                                     			// map::key_type
			   class T,                                       			// map::mapped_type
			   class Compare = std::less<Key>,                   		// map::key_compare
			   class Alloc = std::allocator<ft::pair<const Key,T> >	>	// map::allocator_type
	class map
	{
		public:
			template <class Map>
			class MapIterator;

			typedef Key								key_type;
			typedef T								mapped_type;
			typedef pair<key_type, mapped_type>		value_type;
			typedef Compare							key_compare;
			typedef ValueCompare					value_compare; /* Returns an object that can be used to compare 2 elements, (pair element not key) */
			typedef Alloc							allocator_type;

			typedef allocator_type::reference		reference;
			typedef allocator_type::const_reference	const_reference;
			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;
		
			/* When dereferencing iterator we access a std::pair<Key, T>, just like vector access T */
			typedef MapIterator< map<Key, T, Compare, Alloc> >				iterator;
			typedef MapIterator< map<const Key, const T, Compare, Alloc> >	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			/* Identical to iterator_traits<iterator>::size_type/difference_type */
			typedef ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef ft::iterator_traits<iterator>::size_type		size_type;
	
		private:
			typedef typename RBTree<value_type, Compare>::node_pointer			node_pointer;
		
			allocator_type						_alloc;
			RBTree<value_type, value_compare>	_tree;
			Compare								_comp;

		public:
			/* Iterators */
			iterator		begin() { return (iterator(this->_tree.first())); }
			const_iterator	begin() const { return const_iterator(this->_tree.first()); }

			iterator		end() { return (iterator(this->_tree.last())); }
			const_iterator	end() const { return (const_iterator(this->_tree.last())); }

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

				if (alreadyExists != nullptr) /* Value already in tree */
					return (ft::make_pair(iterator(alreadyExists), false));
				
				this->_tree.insert(val);
				return (ft::make_pair(this->_tree.search(val), true));
			}

			/* Insert as close to position as possible (to optimize insertion we give hint) \.
			   Since we don't want our container to be fully optimized, just call insert coz im lazy */
			iterator insert(iterator position, const value_type& val)
			{
				return (this->insert(val).first());
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

				if (this->_tree.search(tmp_pair) != nullptr)
				{
					this->_tree.remove(tmp_pair);
					return_val = 1;
				}
				return (return_val);
			}

			void erase (iterator first, iterator last)
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
			class ValueCompare
			{
				public:
					/* Work like: 'ValueCompare comp; comp(pouet, pouet) == true' */
					bool operator()(value_type lhs, value_type rhs)
					{
						return (_comp(lhs.first(), rhs.first()));
					}
			};

			value_compare value_comp() const { return (ValueCompare()); }

			/* Operations */
			iterator find (const key_type& k)
			{
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == nullptr)
					return (this->end());
				
				return (iterator(value));
			}

			const_iterator find (const key_type& k) const
			{
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == nullptr)
					return (this->end());
				
				return (const_iterator(value));
			}

			template <typename Pair>
			class MapIterator
			{
				private:
					typedef typename ft::iterator<ft::bidirectional_iterator_tag, Pair>	iterator;
					typedef typename RBTree<value_type, Compare>::node_pointer			node_pointer;

				public:
					typedef typename iterator::iterator_category	iterator_category;
					typedef typename iterator::value_type			value_type;
					typedef typename iterator::reference			reference;
					typedef typename iterator::pointer				pointer;

					typedef ptrdiff_t	difference_type;
					typedef size_t		size_type;

					MapIterator()

				private:
					node_pointer _node;
			}


	};

}

#endif