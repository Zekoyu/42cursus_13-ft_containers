/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 13-03-2022  by  `-'                        `-'                  */
/*   Updated: 13-03-2022 14:35 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDITERATOR_HPP
# define RANDITERATOR_HPP

#include "iterators.hpp"


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
	template <typename T, bool IsConst = false>
	class RandIterator : public ft::iterator<
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
			RandIterator(T* ptr = nullptr) { _ptr = ptr; }
			RandIterator(const RandIterator<T>& it) { this->_ptr = it._ptr; }
			~RandIterator() { }

			RandIterator<T, IsConst>& operator=(const RandIterator<T, IsConst>& it) { this->_ptr = it._ptr; return (*this); }

			// Allow conversion from non-const to const, but not the other way around
			operator RandIterator<T, true>() { return (RandIterator<T, true>)(this->_ptr); }

	};

}

#endif