/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 16-03-2022  by  `-'                        `-'                  */
/*   Updated: 16-03-2022 16:22 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pairs.hpp"
#include "RedBlackTree.hpp"
#include <iostream>
#include <functional>
#include <memory>

namespace ft
{
	template <class Key,
			  class T,
			  class Compare = std::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> >
			 >
	class map
	{
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const key_type, mapped_type>	value_type;
			
			// Takes PAIR objects (like the one stored by the tree) and compare them using only the key
			struct ValueCompare
			{
				// Work like: 'ValueCompare comp; comp(pair, pair) == true'
				bool operator()(value_type lhs, value_type rhs) const
				{
					Compare comp;
					return (comp(lhs.first, rhs.first));
				}
			};

			typedef Compare									key_compare;
			typedef ValueCompare							value_compare;
			typedef Alloc									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
		
		private:
			typedef RedBlackTree<value_type, value_compare, allocator_type> tree_type;

		public:
			typedef typename tree_type::iterator		iterator;
			typedef typename tree_type::const_iterator	const_iterator;

			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

			typedef ptrdiff_t	difference_type;
			typedef size_t		size_type;

		private:
			key_compare		_comp;
			allocator_type	_alloc;
			tree_type		_tree;

			// Pretty easy but I'm smartn't so this won't have my monkey brain
			bool isInf(const value_type& lhs, const value_type& rhs) const
			{ return (this->_comp(lhs, rhs)); }

			bool isInfOrEqual(const value_type& lhs, const value_type& rhs) const
			{ return (this->isInf(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isSup(const value_type& lhs, const value_type& rhs) const
			{ return (!this->isInf(lhs, rhs) && !this->isEq(lhs, rhs)); }

			bool isSupOrEqual(const value_type& lhs, const value_type& rhs) const
			{ return (this->isSup(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isEq(const value_type& lhs, const value_type& rhs) const
			{ return (!this->_comp(lhs, rhs) && !this->_comp(rhs, lhs)); }

		public:
			// Default constructor / empty
			explicit map(const key_compare& comp = key_compare(),
			             const allocator_type& alloc = allocator_type())
						 : _comp(comp), _alloc(alloc), _tree() { }

			// Range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
			     const key_compare& comp = key_compare(),
				 const allocator_type& alloc = allocator_type())
				 : _comp(comp), _alloc(alloc), _tree()
			{
				while (first != last)
				{
					this->_tree.insert(*first);
					++first;
				}
			}

			// Copy constructor, deep copy tree
			map(const map& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) { }

			/********** Iterators **********/
			iterator		begin() { return (this->_tree.begin()); }
			const_iterator	begin() const { return (this->_tree.begin()); }

			iterator		end() { return (this->_tree.end()); }
			const_iterator	end() const { return (this->_tree.end()); }

			reverse_iterator		rbegin() { return (this->_tree.rbegin()); }
			const_reverse_iterator	rbegin() const { return (this->_tree.rbegin()); }

			reverse_iterator		rend() { return (this->_tree.rend()); }
			const_reverse_iterator	rend() const { return (this->_tree.rend()); }

			/********** Capacity **********/
			bool empty() const { return (this->_tree.size() == 0); }
			size_type size() const { return (this->_tree.size()); }
			size_type max_size() const { return (this->_alloc.max_size()); }

			/********** Modifiers **********/

			// tree.insert returns true if added, false if already present
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				return (ft::make_pair(iterator(this->_tree.search(val)), this->_tree.insert(val)));
			}

			// Should use position for optimization, but meh
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

			
			size_type erase(const key_type& k)
			{
				size_type return_val = 0;
				// Create a temporary to make it easier to find k
				value_type  tmp_pair(k, mapped_type());

				if (this->_tree.search(tmp_pair) != NULL)
				{
					this->_tree.remove(tmp_pair);
					return_val = 1;
				}
				return (return_val);
			}
			
			void erase(iterator position)
			{
				this->_tree.remove(*position);
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					this->_tree.remove(*first++);
			}


			void swap(map& x)
			{
				tree_type& tmp_tree = this->_tree;
				key_compare& tmp_comp = this->_comp;
				allocator_type& tmp_alloc = this->_alloc;

				this->_tree = x._tree;
				this->_comp = x._comp;
				this->_alloc = x._alloc;

				x._tree = tmp_tree;
				x._comp = tmp_comp;
				x._alloc = tmp_alloc;
			}

			void clear() { this->_tree.clear(); }

			/********** Element accesses **********/
			// Returns a reference to the mapped value,
			// it's either the value found corresponding to the key, or the newly inserted one in the other case
			// Retrieve the iterator returned by insert, then return a reference to the mapped_type (second in pair)
			mapped_type& operator[](const key_type& k)
			{ return (*(this->insert(ft::make_pair(k, mapped_type())).first)).second }
			
			/********** Observers **********/
			key_compare key_comp() const { return (key_comp()); }

			// Will create a copy since it's not returned by reference
			value_compare value_comp() const { return (this->_comp); }

			/********** Operations **********/
			iterator find(const key_type& k)
			{
				// Create a temporary to make it easier to find k
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == NULL)
					return (this->end());
				
				return (iterator(value));
			}

			const_iterator find(const key_type& k) const
			{
				// Create a temporary to make it easier to find k
				value_type  tmp_pair(k, mapped_type());

				node_pointer value = this->_tree.search(tmp_pair);
				if (value == NULL)
					return (this->end());
				
				return (const_iterator(value));
			}

			// Returns the count of key in the tree, in map it's always 0 or 1
			size_type count(const key_type& k) const
			{
				value_type tmp_pair(k, mapped_type());

				if (this->_tree.search(tmp_pair) != NULL)
					return (1);
				return (0);
			}

			// Returns an iterator pointing to the first element in the container whose key 
			// is not considered to go before k (i.e., either it is equivalent or goes after).
			iterator lower_bound(const key_type& k)
			{
				node_pointer curr = this->_tree.first();
				
				while (curr != NULL && isInf(curr->data.first, k))
					curr == tree_type::inorderNext(curr);
			}

	};
}

#endif