/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 13-03-2022  by  `-'                        `-'                  */
/*   Updated: 13-03-2022 19:14 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include "iterators.hpp"
#include "enable_if.hpp"
#include <iostream>

namespace ft
{

	template <bool Flag, class IsTrue, class IsFalse>
	struct choose;

	template <class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse>
	{
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse>
	{
		typedef IsFalse type;
	};

	/* If IsConst, types will be const, otherwise they will not, in all cases T is non-const */
	/* https://stackoverflow.com/questions/2150192/how-to-avoid-code-duplication-implementing-const-and-non-const-iterators */
	/* https://www.cplusplus.com/reference/iterator/RandomAccessIterator/ */
	template <typename T, bool IsConst = false>
	class VectIterator : public ft::iterator<
											 ft::random_access_iterator_tag,
											 typename choose<IsConst, const T, T>::type
											>
	{
		protected:
			typedef typename ft::iterator<ft::random_access_iterator_tag, typename choose<IsConst, const T, T>::type> it;
			// Our pointer is always non-const, only gets returned as const in case of const iterator
			T* _ptr;

		public:
			// Combines default constructor and assignation constructor
			VectIterator(T* ptr = NULL) { _ptr = ptr; }
			VectIterator(const VectIterator<T, IsConst>& it) { this->_ptr = it._ptr; }
			~VectIterator() { }

			VectIterator<T, IsConst>& operator=(const VectIterator<T, IsConst>& it) { this->_ptr = it._ptr; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator VectIterator<T, true>() { return (VectIterator<T, true>)(this->_ptr); }


			/********** Relational operators **********/
			// A + n
			VectIterator<T, IsConst> operator+(typename it::difference_type n) const { return (VectIterator<T, IsConst>(this->_ptr + n)); }

			// A - n
			VectIterator<T, IsConst> operator-(typename it::difference_type n) const { return (VectIterator<T, IsConst>(this->_ptr - n)); }

			// *A
			typename it::reference operator*() const { return (*this->_ptr); }

			// A->m (When can this be used ?? Idk, didn't found)
			typename it::pointer operator->() const { return (this->_ptr); }

			// ++A
			VectIterator<T, IsConst>& operator++() { ++this->_ptr; return (*this); }

			// A++
			VectIterator<T, IsConst>& operator--() { --this->_ptr; return (*this); }

			// --A
			VectIterator<T, IsConst> operator++(int) { VectIterator<T, IsConst> tmp = *this; ++(*this); return (tmp); }

			// A--
			VectIterator<T, IsConst> operator--(int) { VectIterator<T, IsConst> tmp = *this; --(*this); return (tmp); }

			// A += n
			VectIterator<T, IsConst>& operator+=(typename it::difference_type n) { this->_ptr += n; return (*this); }

			// A -= n
			VectIterator<T, IsConst>& operator-=(typename it::difference_type n) { this->_ptr -= n; return (*this); }
			
			// A[n]
			typename it::reference operator[](typename it::difference_type n) { return (this->_ptr[n]); }

			/********** Friend relational operators, to allow const and non-const mixed **********/
			// Operators on possibly different (const / non-const) iterators

			// A - B, Uses IteRight for SNIFAE to force using operator-(difference_type) for 'begin() - 2' for instance
			template <class IteLeft, class IteRight>
			friend typename IteRight::difference_type operator-(const IteLeft& lhs, const IteRight& rhs);

			// n + A
			template <typename Type>
			friend VectIterator<Type> operator+(typename VectIterator<Type>::difference_type n, const VectIterator<Type>& rhs);

			// A == B
			template <class IteLeft, class IteRight>
			friend bool operator==(const IteLeft& lhs, const IteRight& rhs);

			// A != B
			template <class IteLeft, class IteRight>
			friend bool operator!=(const IteLeft& lhs, const IteRight& rhs);

			// A < B
			template <class IteLeft, class IteRight>
			friend bool operator<(const IteLeft& lhs, const IteRight& rhs);

			// A <= B
			template <class IteLeft, class IteRight>
			friend bool operator<=(const IteLeft& lhs, const IteRight& rhs);

			// A > B
			template <class IteLeft, class IteRight>
			friend bool operator>(const IteLeft& lhs, const IteRight& rhs);

			// A >= B
			template <class IteLeft, class IteRight>
			friend bool operator>=(const IteLeft& lhs, const IteRight& rhs);
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
		++A ✅
		A++ ✅
		*A++ ✅
		--A ✅
		A-- ✅
		*A-- ✅

		A + n ✅
		n + A ✅

		A - n ✅
		A - B ✅

		A < B ✅
		A > B ✅
		A <= B ✅
		A >= B ✅

		A += n
		A -= n

		A[n] ✅
	*/

	// n + A
	template <typename T>
	VectIterator<T> operator+(typename VectIterator<T>::difference_type n, const VectIterator<T>& rhs) { return (VectIterator<T>(rhs._ptr + n)); }

	// A - B
	// Will automatically not compile if IteLeft and IteRight are not of the same type (eg. bool pointer and int pointer)
	// Only operator- returns a difference type, trying to print it1 + it2 will faill on std
	template <class IteLeft, class IteRight>
	typename IteRight::difference_type operator-(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr - rhs._ptr); }

	// A == B / B == A
	template <class IteLeft, class IteRight>
	bool operator==(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr == rhs._ptr); }

	// A != B / B != A
	template <class IteLeft, class IteRight>
	bool operator!=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr != rhs._ptr); }

	// A < B
	template <class IteLeft, class IteRight>
	bool operator<(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr < rhs._ptr); }

	// A <= B
	template <class IteLeft, class IteRight>
	bool operator<=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr <= rhs._ptr); }

	// A > B
	template <class IteLeft, class IteRight>
	bool operator>(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr > rhs._ptr); }

	// A >= B
	template <class IteLeft, class IteRight>
	bool operator>=(const IteLeft& lhs, const IteRight& rhs) { return (lhs._ptr >= rhs._ptr); }

}

#endif