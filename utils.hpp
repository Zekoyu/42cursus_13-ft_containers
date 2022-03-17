/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 14-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 17:18 by                                             */
/*                                                                            */
/* ************************************************************************** */

// FT_UTILS instead of UTILS because otherwise 42 Containator thinks utils is already defined
#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

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


	// Default, T and U are different
	template <class T, class U>
	struct is_same { static const bool value = false; };

	// Specialization, T and T are the same
	template<class T>
	struct is_same<T, T> { static const bool value = true; };

}

#endif