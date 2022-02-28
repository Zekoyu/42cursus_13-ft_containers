/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 28-02-2022 17:07 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

/* Iterator traits of another iterator are value from the former */
template <class Iterator>
struct iterator_traits /* struct so that it's public by default */
{
	typedef Iterator::difference_type	difference_type;
	typedef Iterator::value_type		value_type;
	typedef Iterator::pointer			pointer;
	typedef Iterator::reference			reference;
	typedef Iterator::iterator_category	iterator_category;
};

/* Iterator traits of a class pointer are basically the class values themselves */


#endif