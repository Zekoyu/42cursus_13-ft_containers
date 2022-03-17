/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 17-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 22:40 by                                             */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 16-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 22:40 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include "pairs.hpp"
#include "comparisons.hpp"
#include "RedBlackTree.hpp"

#include <functional>
#include <memory>

namespace ft
{
	// In a set, elements in the container
	template <class T,
			  class Compare = std::less<T>,
			  class Alloc = std::allocator<T>
			 >
	class set
	{
		public:
			typedef T key_type;
			typedef T value_type;

			typedef Compare	key_compare;
			typedef Compare	value_compare;
			typedef Alloc	allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
		
		private:
			typedef RedBlackTree<value_type, value_compare, allocator_type> tree_type;

		public:
			// Since in a set all values are const, simply use the const_iterator as iterator, smort
			typedef typename tree_type::const_iterator	iterator;
			typedef typename tree_type::const_iterator	const_iterator;
			// Same for reverse
			typedef typename tree_type::const_reverse_iterator	reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

			typedef ptrdiff_t	difference_type;
			typedef size_t		size_type;

		private:
			value_compare	_comp;
			allocator_type	_alloc;
			tree_type		_tree;

			// Pretty easy but I'm smartn't so this won't have my monkey brain
			bool isInf(const key_type& lhs, const key_type& rhs) const
			{ return (this->_comp(lhs, rhs)); }

			bool isInfOrEqual(const key_type& lhs, const key_type& rhs) const
			{ return (this->isInf(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isSup(const key_type& lhs, const key_type& rhs) const
			{ return (!this->isInf(lhs, rhs) && !this->isEq(lhs, rhs)); }

			bool isSupOrEqual(const key_type& lhs, const key_type& rhs) const
			{ return (this->isSup(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isEq(const key_type& lhs, const key_type& rhs) const
			{ return (!this->_comp(lhs, rhs) && !this->_comp(rhs, lhs)); }

		public:
			// Default constructor / empty
			explicit set(const key_compare& comp = key_compare(),
			             const allocator_type& alloc = allocator_type())
						 : _comp(comp), _alloc(alloc), _tree() { }

			// Range constructor
			template <class InputIterator>
			set(InputIterator first, InputIterator last,
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
			set(const set& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) { }

			// Assignation operator
			set& operator=(const set& x)
			{
				this->_comp = x._comp;
				this->_alloc = x._alloc;
				this->_tree = x._tree;
				
				return (*this);
			}

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
			size_type max_size() const { return (this->_tree.max_size()); }

			/********** Modifiers **********/

			// tree.insert returns true if added, false if already present
			// So just add the value anyway, and then search for it since map has unique keys
			ft::pair<iterator, bool> insert(const value_type& val)
			{
				bool inserted = this->_tree.insert(val);
				return (ft::make_pair(iterator(this->_tree.search(val)), inserted));
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

				if (this->_tree.search(k) != NULL)
				{
					this->_tree.remove(k);
					return_val = 1;
				}
				return (return_val);
			}
			
			void erase(iterator position)
			{
				this->_tree.remove(*position);
			}

			// Since iterator being erased is invalidated on remove, first save next node
			void erase(iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					tmp = first;
					++first;
					this->_tree.remove(*tmp);
				}
			}

			void swap(set& x)
			{
				key_compare tmp_comp = this->_comp;
				allocator_type tmp_alloc = this->_alloc;

				this->_comp = x._comp;
				this->_alloc = x._alloc;

				x._comp = tmp_comp;
				x._alloc = tmp_alloc;

				this->_tree.swap(x._tree);
			}

			void clear() { this->_tree.clear(); }
			
			/********** Observers **********/
			key_compare key_comp() const { return (this->_comp); }

			// Will create a copy since it's not returned by reference
			value_compare value_comp() const { return (this->_comp); }

			/********** Lookup / Operations **********/
			iterator find(const key_type& k)
			{
				typename tree_type::node_pointer value = this->_tree.search(k);
				if (value == NULL)
					return (this->end());
				
				return (iterator(value));
			}

			const_iterator find(const key_type& k) const
			{
				typename tree_type::node_pointer value = this->_tree.search(k);
				if (value == NULL)
					return (this->end());
				
				return (const_iterator(value));
			}

			// Returns the count of key in the tree, in map it's always 0 or 1
			size_type count(const key_type& k) const
			{
				if (this->_tree.search(k) != NULL)
					return (1);
				return (0);
			}

			// Returns an iterator pointing to the first element in the container whose key 
			// is not considered to go before k (i.e., either it is equivalent or goes after).
			iterator lower_bound(const key_type& k)
			{
				typename tree_type::node_pointer curr = this->_tree.first();
				
				while (curr != NULL && this->isInf(curr->data, k))
					curr = tree_type::inorderSuccessor(curr);

				if (curr == NULL || curr == this->_tree.getDummyEnd())
					return (this->end());

				return (iterator(curr));
			}

			const_iterator lower_bound(const key_type& k) const
			{

				typename tree_type::node_pointer curr = this->_tree.first();
				
				while (curr != NULL && this->isInf(curr->data, k))
					curr = tree_type::inorderSuccessor(curr);

				if (curr == NULL || curr == this->_tree.getDummyEnd())
					return (this->end());

				return (const_iterator(curr));
			}

			iterator upper_bound(const key_type& k)
			{
				typename tree_type::node_pointer curr = this->_tree.first();
				
				while (curr != NULL && !this->isInf(k, curr->data))
					curr = tree_type::inorderSuccessor(curr);

				if (curr == NULL || curr == this->_tree.getDummyEnd())
					return (this->end());

				return (iterator(curr));
			}

			const_iterator upper_bound(const key_type& k) const
			{
				
				typename tree_type::node_pointer curr = this->_tree.first();
				
				while (curr != NULL && !this->isInf(k, curr->data))
					curr = tree_type::inorderSuccessor(curr);

				if (curr == NULL || curr == this->_tree.getDummyEnd())
					return (this->end());

				return (const_iterator(curr));
			}
			
			// Returns a range that includes all elements with a key == k
			// Since map has unique keys, the range is at most 1 long
			/* The function returns a pair, whose member pair::first is the lower bound of the range (the same as lower_bound),
			   and pair::second is the upper bound (the same as upper_bound). */
			ft::pair<iterator, iterator> equal_range(const key_type& k)
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
			{ return (ft::make_pair(this->lower_bound(k), this->upper_bound(k))); }
	
			/********** Allocator **********/
			// Will copy since it doesn't return by reference
			allocator_type get_allocator() const { return (this->_alloc); }
	};

	/********** Non-member overloads **********/
	template <class T, class Compare, class Alloc>
	void swap(ft::set<T, Compare, Alloc>& x, ft::set<T, Compare, Alloc>& y)
	{ x.swap(y); }

	// Notice that none of these operations take into consideration the internal comparison object of either container,
	// but compare the elements (of type value_type) directly.
	template <class T, class Compare, class Alloc>
	bool operator==(const ft::set<T, Compare, Alloc>& lhs,
					const ft::set<T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool operator!=(const ft::set<T, Compare, Alloc>& lhs,
					const ft::set<T, Compare, Alloc>& rhs)
	{ return (!(lhs == rhs)); }

	// https://www.cplusplus.com/reference/map/map/operators/
	template <class T, class Compare, class Alloc>
	bool operator<(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Compare, class Alloc>
	bool operator<=(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T, class Compare, class Alloc>
	bool operator>(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs)
	{ return (rhs < lhs); } // Either <= or >

	template <class T, class Compare, class Alloc>
	bool operator>=(const ft::set<T, Compare, Alloc>& lhs, const ft::set<T, Compare, Alloc>& rhs)
	{ return (!(lhs < rhs)); } // Either < or >=

}

#endif