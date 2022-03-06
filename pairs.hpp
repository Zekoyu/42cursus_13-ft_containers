/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 06-03-2022  by  `-'                        `-'                  */
/*   Updated: 06-03-2022 13:32 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIRS_HPP
# define PAIRS_HPP

namespace ft
{
	/* This class couples together a pair of values, which may be of difference types (T1 and T2)
	elements are stored as first and second members, respectively of type T1 and T2 */
	template <class T1, class T2>
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1	first;
		T2	second;

		/* Default constructor, values are initialized */
		pair() : first(), second() { }

		/* Copy constructor, values initialized with content of pr */
		template<class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) { }

		/* Initialization constructor, values initialized with given arguments */
		pair(const first_type &a, const second_type& b) : first(a), second(b) { }

		/* The assignment operator is implicitly declared */
	};

	/* Two pair objects compare equal to each other if both their first members compare equal to each other
	   and both their second members compare also equal to each other (in both cases using operator== for the comparison).

	   Similarly, operators <, >, <= and >= perform a lexicographical comparison on the sequence formed by members first and second
	   (in all cases using operator< reflexively for the comparisons). */
	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	/* Only uses operator< of members */
	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || !(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(rhs < lhs)); /* If rhs >= lhs (rhs !< lhs), then lhs <= rhs */
	}

	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs < rhs));
	}

}

#endif