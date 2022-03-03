/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 03-03-2022 13:37 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include <memory>

namespace ft
{

	// > > instead of >> because otherwise C++ might think it's a bitshift
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T								value_type;
			typedef Allocator						allocator_type;
			/* All of these could be used with value_type for the default allocator, but maybe not custom ones */
			typedef allocator_type::reference		reference; /* Same as value_type& */
			typedef allocator_type::const_reference	const_reference; /* Same as const value_type& */
			typedef allocator_type::pointer			pointer; /* Same as value_type* */
			typedef allocator_type::const_pointer	const_pointer; /* Same as const value_type* */
			
			class RandomAccessIterator
			
	};
	
}
