/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 14-03-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 13:23 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

	template <bool Flag, class IsTrue, class IsFalse>
	struct chose;

	template <class IsTrue, class IsFalse>
	struct chose<true, IsTrue, IsFalse>
	{
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct chose<false, IsTrue, IsFalse>
	{
		typedef IsFalse type;
	};

}

#endif