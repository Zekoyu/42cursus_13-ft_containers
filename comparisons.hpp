/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 05-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 13:58 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARISONS_HPP
# define COMPARISONS_HPP

namespace ft
{
	// Ranges are almost always [first, last), which means first included, last excluded
	// "Default" version simply uses operator ==, typically only required operators are == and < for any comparisons
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* A predicate is a function returning a boolean / if the member has a bool operator() overload
	   which is used in cases like if (i), if (ptr) etc. to return true or false.
	   A binary predicate takes two arguments and unary takes one, in this case a simple
	   predicate would just be a ==, if false return false */
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	}

	/* Return true if first1-last1 is lexicographically less than first2-last2.
	   If only 1 element (from begin to end) is strictly smaller in first1 than first2, it
	   is considered lexicographically smaller. Same the opposite way (first2 < first1).
	   In case they are equal, the shortest one is considered smaller, if they are both
	   the exact same, return false */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
    							  InputIterator2 first2, InputIterator2 last2)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2); /* If first1 is shorter, return true, since they are equal but first2 is longer */
	}

	/* Same with a predicate, comp should return true if first argument is smaller than second */
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
    							  InputIterator2 first2, InputIterator2 last2,
								  BinaryPredicate comp)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			++first1;
			++first2;
		}
		return (first1 == last1 && first2 != last2);
	}

}

#endif