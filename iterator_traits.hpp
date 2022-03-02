/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 02-03-2022 10:08 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft
{

	struct	random_access_iterator_tag { };

	/* Iterator traits of another iterator are value taken from it */
	template <class Iterator>
	struct iterator_traits /* struct so that it's public by default */
	{
		typedef Iterator::difference_type	difference_type; /* Difference between 2 iterators (used by std::distance, typically int for iterators, ptrdiff_t for pointers) */
		typedef Iterator::value_type		value_type;
		typedef Iterator::pointer			pointer;
		typedef Iterator::reference			reference;
		typedef Iterator::iterator_category	iterator_category;
	};

	/* Iterator traits of a pointer are just the value pointer to by this pointer (for classes with no iterators but just raw pointer) */
	template <class T>
	struct iterator_traits<T*> /* Specialization of iterator_traits with any pointer type (same as iterator_traits<char> for specializing char for instance) */
	{
		typedef Iterator::difference_type	ptrdiff_t; /* Literally the distance type (result of substraction) between 2 pointer */
		typedef Iterator::value_type		T;
		typedef Iterator::pointer			T*;
		typedef Iterator::reference			T&;
		typedef Iterator::iterator_category	random_access_iterator_tag; /* Since it's a pointer, it should be pointing to contiguous memory, so can be accessed at random */
	};

	/* Same specialization for pointers to const */
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef Iterator::difference_type	ptrdiff_t;
		typedef Iterator::value_type		T;
		typedef Iterator::pointer			const T*;
		typedef Iterator::reference			const T&;
		typedef Iterator::iterator_category	random_access_iterator_tag;
	};

}

#endif