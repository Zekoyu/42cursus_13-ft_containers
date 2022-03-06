/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 06-03-2022  by  `-'                        `-'                  */
/*   Updated: 06-03-2022 19:04 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pairs.hpp"

#include <memory>
#include <functional>

namespace ft
{

	template < class Key,                                     			// map::key_type
			   class T,                                       			// map::mapped_type
			   class Compare = std::less<Key>,                   		// map::key_compare
			   class Alloc = std::allocator<ft::pair<const Key,T> >	>	// map::allocator_type
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<key_type, mapped_type>					value_type;
			typedef Compare										key_compare;
			typedef value_comp									value_compare;
			typedef Alloc										allocator_type;
			typedef allocator_type::reference					reference;
			typedef allocator_type::const_reference				const_reference;
			typedef allocator_type::pointer						pointer;
			typedef allocator_type::const_pointer				const_pointer;
			typedef BiIterator< map<Key, T, Compare, Alloc> >	iterator;
			typedef BiIterator< map<Key, T, Compare, Alloc> >	const_iterator;
	};

}

#endif