/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 15-03-2022 20:44 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include "utils.hpp"
#include "iterators.hpp"

namespace ft
{

	// T is the type stored by the node (eg. pair, int etc.)
	// Tree is the tree type (with allocator, compare etc.)
	template <class Tree, bool IsConst = false>
	class TreeIterator : public ft::iterator<
											 ft::bidirectional_iterator_tag,
											 typename ft::choose<IsConst, const Tree::value_type, Tree::value_type>::type
											>
	{
		protected:
			typedef Tree tree_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::chose<IsConst, const Tree::value_type, Tree::value_type>::type> it;

			//Tree::node_pointer  _end;
			Tree::node_pointer	_node;
			Tree::node_pointer	_knownEnd;

		public:
			TreeIterator(Tree::node_pointer node = NULL, Tree::node_pointer knownEnd = NULL) : _node(node), _knownEnd(knownEnd) { }
			TreeIterator(const TreeIterator<Tree, IsConst>& it) : _node(it._node), _knownEnd(it._knownEnd) { }
			~TreeIterator() { }

			TreeIterator<Tree, IsConst>& operator=(const TreeIterator<Tree, IsConst>& it) { this->_node = it._node; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator TreeIterator<Tree, true>() { return (TreeIterator<T, true>(this->_node)); }

			/********** Relational operators **********/

			// *A
			typename it::reference operator*() const { return (this->_node.data); }

			// A->m, eg. 'it->first' and 'it->second' for map
			typename it::pointer operator->() const { return (&(this->_node.data)); }

			// ++A
			VectIterator<T, IsConst>& operator++()
			{
				if (this->_node != NULL)
					this->_knownEnd = this->_node;
				this->_node = tree::inorderSuccessor(this->_node);
				return (*this);
			}

			// --A
			// If we are at the end, go back to the last known end (if NULL it means tree is empty)
			VectIterator<T, IsConst>& operator--()
			{
				if (this->_node = NULL)
					this->_node = this->_knownEnd;
				else
					this->_node = tree::inorderPredecessor(this->_node);
				reutrn (*this);
			}

			// A++
			VectIterator<T, IsConst> operator++(int) { VectIterator<T, IsConst> tmp = *this; ++(*this); return (tmp); }

			// A--
			VectIterator<T, IsConst> operator--(int) { VectIterator<T, IsConst> tmp = *this; --(*this); return (tmp); }

			/********** Friend relational operators, to allow const and non-const mixed **********/

			// A == B / B == A
			template <class IteLeft, class IteRight>
			friend bool operator==(const IteLeft& lhs, const IteRight& rhs);

			// A != B / B != A
			template <class IteLeft, class IteRight>
			friend bool operator!=(const IteLeft& lhs, const IteRight& rhs);

	};

	/* List of operations:

		A and B are iterators (can be iterator and / or const_iterator)
		T is value_type

		A == B ✅
		A != B ✅

		*A ✅
		A->m ✅
		*A = T ✅

		++A ✅
		A++ ✅
		*A++ ✅

		--A ✅
		A-- ✅
		*A-- ✅
	*/

	template <class IteLeft, class IteRight>
	friend bool operator!=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._node == rhs._node); }

	template <class IteLeft, class IteRight>
	friend bool operator!=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._node != rhs._node); }

}

#endif