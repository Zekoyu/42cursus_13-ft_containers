/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 05-03-2022  by  `-'                        `-'                  */
/*   Updated: 11-03-2022 10:04 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include "iterators.hpp"

namespace ft
{
	/* Returns a value of type difference_type from the iterator */
	//template<class InputIterator>
	//typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
	//{
	//	/* enable_if random */
	//}

	/* https://stackoverflow.com/questions/2150192/how-to-avoid-code-duplication-implementing-const-and-non-const-iterators */
	template <bool Choose, class TrueCase, class FalseCase>
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
}

#endif