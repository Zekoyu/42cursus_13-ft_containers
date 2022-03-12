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

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
	/* ft::is_integral<int>() is the same as ft::is_integral<int>::value thanks to operator value_type/bool() */
	struct true_type
	{
		typedef bool		value_type;
		typedef true_type	type;

		static const bool value = true; /* public static member constant */

		operator value_type() { return true; }
	};

	struct false_type
	{
		typedef bool		value_type;
		typedef false_type	type;

		static const bool value = false;

		operator value_type() { return false; }
	};

	/* All values are inherited from integral_constant, which is template for true_type and false_type */
	/* Default is_integral (without specialization) means it's not integral */
	template <class T>
	struct is_integral : public false_type { };
	
	template <>
	struct is_integral<bool> : public true_type { };

	template <>
	struct is_integral<char> : public true_type { };

	/* Since C++11 (char16_t char32_t don't exist in C++98)
	template <>
	struct is_integral<char16_t> : public true_type { };

	template <>
	struct is_integral<char32_t> : public true_type { };*/

	/* Wide character for unicode UTF-16 */
	template <>
	struct is_integral<wchar_t> : public true_type { };

	/* C++ consider char, signed char and unsigned char as different types
	   https://stackoverflow.com/questions/16503373/difference-between-char-and-signed-char-in-c */
	template <>
	struct is_integral<signed char> : public true_type { };

	template <>
	struct is_integral<short int> : public true_type { };

	template <>
	struct is_integral<int> : public true_type { };

	template <>
	struct is_integral<long int> : public true_type { };

	template <>
	struct is_integral<long long int> : public true_type { };

	template <>
	struct is_integral<unsigned char> : public true_type { };

	template <>
	struct is_integral<unsigned short int> : public true_type { };

	template <>
	struct is_integral<unsigned int> : public true_type { };

	template <>
	struct is_integral<unsigned long int> : public true_type { };

	template <>
	struct is_integral<unsigned long long int> : public true_type { };

}

#endif