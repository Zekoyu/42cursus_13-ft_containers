/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 14-03-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 23:36 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

#include "iterators.hpp"
#include "enable_if.hpp"
#include "utils.hpp"
#include "RBT.hpp"
#include "pairs.hpp"

namespace ft
{
	template <class Key, class Type, class Node, class Tree, bool IsConst = false>
	class MapIterator : public ft::iterator<
											ft::bidirectional_iterator_tag,
											typename ft::choose<IsConst, const ft::pair<const Key, Type>, ft::pair<const Key, Type> >::type
										   >
	{		
		protected:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::choose<IsConst, const T, T>::type> it;
			typedef ft::pair<const Key, Type> pair_type;
			typedef MapIterator<Key, Type, Node, IsConst> self_type;
			
			Node* _node;
			// end.right = tree.last(), end.left = tree.first()
			Node* _end;

		public:
			MapIterator(Node* node = NULL) { _node = node; }
			MapIterator(const self_type& it) { this->_node = it._node; }
			~MapIterator() { }

			self_type& operator=(const self_type& it) { this->_node = it._node; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator MapIterator<Key, Type, Node, true>() { return (MapIterator<Key, Type, Node, true>(this->_node)); }

			// *A
			typename it::reference operator*() const { return (NULL); return (*this->_node->data); }

			// A->m
			typename it::pointer operator->() const { if (this->_node == NULL) return (NULL); return (this->_node->data); }

			// ++A
			self_type& operator++()
			{
				this->_node = Tree::inorderNext(this->_node); return (*this);
			}

			// --A
			self_type& operator--() { this->_node = Tree::inorderPrev(this->_node); return (*this); }

			// A++
			self_type& operator++(int) { self_type tmp = *this; ++(*this); return (tmp); }

			// A--
			self_type& operator--(int) { self_type tmp = *this; --(*this); return (tmp); }

			// A == B
			template <class IteLeft, class IteRight>
			friend bool operator==(const IteLeft& lhs, const IteRight& rhs);

			// A != B
			template <class IteLeft, class IteRight>
			friend bool operator!=(const IteLeft& lhs, const IteRight& rhs);
	};

	/* List of operations:

		A and B are iterators (can be iterator and / or const_iterator)
		T is value_type
		n is a difference_type

		A == B ✅
		A != B ✅

		*A ✅
		A->m ✅
		*A = T ✅
		
		++A  ✅
		A++ ✅
		*A++ ✅
		--A ✅
		A-- ✅
		*A-- ✅
	*/

	// A == B / B == A
	template <class IteLeft, class IteRight>
	bool operator==(const IteLeft& lhs, const IteRight& rhs) { return (lhs._node == rhs._node); }

	// A != B / B != A
	template <class IteLeft, class IteRight>
	bool operator!=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._node != rhs._node); }


}

#endif