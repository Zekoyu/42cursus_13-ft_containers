/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 16-03-2022 15:49 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "RedBlackTree.hpp"
#include "map.hpp"

#include <iostream>

int main()
{
	typedef ft::map<int, float> type;
	typedef type::iterator it;
	typedef type::reverse_iterator rit;
	
	ft::map<int, float> pouet;
	it begin = pouet.begin();
	it end = pouet.end();
	rit pkqwdopkqpdowd;

	std::cout << "Size of tree is " << pouet.size() << '\n';
	std::cout << "Begin == End ? " << (pouet.begin() == pouet.end()) << '\n';

	pouet.insert(ft::make_pair(50, 10.5));
	pouet.insert(ft::make_pair(1, 1.05));

	std::cout << "Size of tree is " << pouet.size() << '\n';
	std::cout << "Begin == End ? " << (pouet.begin() == pouet.end()) << '\n';

	std::cout << "Begin value = [" << pouet.begin()->first << ", " << pouet.begin()->second << "]" << std::endl;

	std::cout << "++Begin == End ? " << (++begin == pouet.end()) << '\n';
	std::cout << "++Begin == End ? " << (++begin == pouet.end()) << '\n';
	std::cout << "++Begin == End ? " << (++begin == pouet.end()) << '\n';

	rit rbegin = pouet.rbegin();
	rit rend = pouet.rend();

	std::cout << "Rbegin = [" << rbegin->first << ", " << rbegin->second << "]" << std::endl;

	std::cout << "Rbegin++ == Rend ? " << (rbegin++ == pouet.rend()) << std::endl;
	
	std::cout << "Rbegin = [" << rbegin->first << ", " << rbegin->second << "]" << std::endl;
	
	std::cout << "++Rbegin == Rend ? " << (++rbegin == pouet.rend()) << std::endl;

}

