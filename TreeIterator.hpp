/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 19:55 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITERATOR_HPP
# define TREEITERATOR_HPP

#include "utils.hpp"
#include "iterators.hpp"

#define END_NODE_COLOR 2

namespace ft
{

	// T is the type stored by the node (eg. pair, int etc.)
	// Tree is the tree type (with allocator, compare etc.)
	template <class Tree, bool IsConst = false>
	class TreeIterator : public ft::iterator<
											 ft::bidirectional_iterator_tag,
											 typename ft::choose<IsConst, const typename Tree::value_type, typename Tree::value_type>::type
											>
	{
		protected:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<IsConst, const typename Tree::value_type, typename Tree::value_type>::type> it;

			//Tree::node_pointer  _end;
			typename Tree::node_pointer	_node;

		public:
			TreeIterator(typename Tree::node_pointer node = NULL) : _node(node) { }
			TreeIterator(const TreeIterator<Tree, IsConst>& it) : _node(it._node) { }
			~TreeIterator() { }

			TreeIterator<Tree, IsConst>& operator=(const TreeIterator<Tree, IsConst>& it) { this->_node = it._node; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator TreeIterator<Tree, true>() { return (TreeIterator<Tree, true>(this->_node)); }

			/********** Relational operators **********/

			// *A
			typename it::reference operator*() const { return (this->_node->data); }

			// A->m, eg. 'it->first' and 'it->second' for map
			typename it::pointer operator->() const { return (&(this->_node->data)); }

			// ++A
			TreeIterator<Tree, IsConst>& operator++()
			{
				if (this->_node->color == END_NODE_COLOR)
					return (*this);
				this->_node = Tree::inorderSuccessor(this->_node);
				return (*this);
			}

			// --A
			TreeIterator<Tree, IsConst>& operator--()
			{
				if (Tree::inorderPredecessor(this->_node) == NULL)
					return (*this);
				this->_node = Tree::inorderPredecessor(this->_node);
				return (*this);
			}

			// A++
			TreeIterator<Tree, IsConst> operator++(int) { TreeIterator<Tree, IsConst> tmp = *this; ++(*this); return (tmp); }

			// A--
			TreeIterator<Tree, IsConst> operator--(int) { TreeIterator<Tree, IsConst> tmp = *this; --(*this); return (tmp); }

			/********** Friend relational operators, to allow const and non-const mixed **********/

			// Only takes TreeIterator as argument, so we don't have redefitions / conflicts when including multiple iterators
			// files with iterators, there is a redefinition from vector iterator
			// A == B / B == A
			template <class LTree, bool LIsConst, class RTree, bool RIsConst>
			friend bool operator==(const TreeIterator<LTree, LIsConst>& lhs, const TreeIterator<RTree, RIsConst>& rhs);

			// A != B / B != A
			template <class LTree, bool LIsConst, class RTree, bool RIsConst>
			friend bool operator!=(const TreeIterator<LTree, LIsConst>& lhs, const TreeIterator<RTree, RIsConst>& rhs);

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

	template <class LTree, bool LIsConst, class RTree, bool RIsConst>
	bool operator==(const TreeIterator<LTree, LIsConst>& lhs, const TreeIterator<RTree, RIsConst>& rhs)
	{ return (lhs._node == rhs._node); }

	template <class LTree, bool LIsConst, class RTree, bool RIsConst>
	bool operator!=(const TreeIterator<LTree, LIsConst>& lhs, const TreeIterator<RTree, RIsConst>& rhs)
	{ return (lhs._node != rhs._node); }

}

#endif