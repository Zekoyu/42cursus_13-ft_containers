/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 14-03-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 18:36 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

#include "iterators.hpp"
#include "enable_if.hpp"
#include "utils.hpp"
#include "RBT.hpp"

namespace ft
{
	template <class T, class Node, bool IsConst = false>
	class MapIterator : public ft::iterator<
											ft::bidirectional_iterator_tag,
											typename ft::chose<IsConst, const T, T>::type
											>
	{		
		protected:	
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, typename ft::chose<IsConst, const T, T>::type> it;
			
			Node* _node;

		public:
			MapIterator(Node* node = NULL) { _node = node; }
			MapIterator(const MapIterator<T, Node, IsConst>& it) { this->_node = it._node; }
			~MapIterator() { }

			MapIterator<T, Node, IsConst>& operator=(const MapIterator<T, Node, IsConst>& it) { this->_node = it._node; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator MapIterator<T, Node, true>() { return (MapIterator<T, Node, true>(this->_node)); }

			// *A
			typename it::reference operator*() const { return (NULL); return (*this->_node->data); }

			// A->m
			typename it::pointer operator->() const { if (this->_node == NULL) return (NULL); return (this->_node->data); }

			// ++A
			MapIterator<T, Node, IsConst>& operator++() { this->_node = RBTree<T>::inorderNext(this->_node); return (*this); }

			// --A
			MapIterator<T, Node, IsConst>& operator--() { this->_node = RBTree<T>::inorderPrev(this->_node); return (*this); }

			// A++
			MapIterator<T, Node, IsConst>& operator++(int) { MapIterator<T, Node, IsConst> tmp = *this; ++(*this); return (tmp); }

			// A--
			MapIterator<T, Node, IsConst>& operator--(int) { MapIterator<T, Node, IsConst> tmp = *this; --(*this); return (tmp); }

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