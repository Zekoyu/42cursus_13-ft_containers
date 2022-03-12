/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 05-03-2022  by  `-'                        `-'                  */
/*   Updated: 05-03-2022 14:31 by                                             */
/*                                                                            */
/* ************************************************************************** */
#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{

	/* If B is false, no typedef */
	template<bool B, class T = void>
	struct enable_if {};
	
	/* Otherwise if it is (template specialization), then type = T */
	template<class T>
	struct enable_if<true, T> { typedef T type; };
	
}

#endif