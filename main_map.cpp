/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 11-03-2022 17:19 by                                             */
/*                                                                            */
/* ************************************************************************** */

//#include "stack.hpp"
//#include <iostream>
//#include "iterator_traits.hpp"
//#include "vector.hpp"
#include <vector>
#include <iostream>
#include "map.hpp"
#include <string>

#define KEY_TYPE	int
#define VAL_TYPE	std::string
#define LIB			ft

/*
template <typename Map>
void	printMap(Map v)
{
	std::cout << "Map content: ";
	for (typename Map::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename Map>
void	reversePrintMap(Map v)
{
	std::cout << "Reverse Map content: ";
	for (typename Map::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
*/

/*
template <typename Iterator>
void	modifyContent(Iterator begin, Iterator end)
{
	while (begin != end)
	{
		*begin += 1;
		++begin;
	}
	std::cout << "Successfully modified content" << std::endl;
}*/

int main()
{
	typedef ft::map<KEY_TYPE, VAL_TYPE>	map;
	
	map	v;

	std::cout << "Size: " << v.size() << std::endl;
	v.insert(ft::make_pair(1, "pouet"));
	std::cout << "Size: " << v.size() << std::endl;
	v.erase(0);
	std::cout << "Size: " << v.size() << std::endl;
	v.erase(1);
	//std::cout << "Size: " << v.size() << std::endl;

//	std::cout << "Len: " << (v1.end() - v1.begin()) << std::endl; 
	
	//test_vector<vector>(v);
	//modifyContent(v.begin(), v.end());
}