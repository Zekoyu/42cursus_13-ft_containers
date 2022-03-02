/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 02-03-2022 10:35 by                                             */
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
			typedef allocator_type::reference		reference;
			typedef allocator_type::const_reference	const_reference;
			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;
			
			
	};
	
}
