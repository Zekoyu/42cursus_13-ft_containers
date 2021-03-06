/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 17-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 19:31 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

int main()
{
	ft::map<int, float> map;

	map[1] = 2.5;
	map[2] = 5.5;
	map[3] = 10.5;

	map.clear();

	map[1] = 2.5;
	map[2] = 5.5;

	for (ft::map<int, float>::const_iterator it = map.end(); it != map.begin(); it--)
	{
		if (it != map.end())
			std::cout << "It val is " << it->first << std::endl;
	}

	
}