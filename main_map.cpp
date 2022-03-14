/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 12-03-2022 15:00 by                                             */
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

#include <map>

#define POUET std
int main()
{
	typedef POUET::map<KEY_TYPE, VAL_TYPE>	map;
	typedef typename map::iterator			it;
	typedef typename map::reverse_iterator	rit;
	map	v;



	//std::cout << "Size: " << v.size() << std::endl;
	//v.insert(POUET::make_pair(1, "pouet"));
	//std::cout << "Size: " << v.size() << std::endl;
	//v.erase(0);
	//std::cout << "Size: " << v.size() << std::endl;
	//v.erase(1);
	//std::cout << "Size: " << v.size() << std::endl;

	v.insert(POUET::make_pair(10, "Salut"));
	v.insert(POUET::make_pair(20, "espece"));
	v.insert(POUET::make_pair(30, "de"));
	v.insert(POUET::make_pair(40, "beau"));
	v.insert(POUET::make_pair(50, "gosse"));

	for (it b = v.begin(); b != v.end(); ++b)
	{
		std::cout << (*b).second << ' ';
	}
	std::cout << std::endl;

	for (rit rb = v.rbegin(); rb != v.rend(); ++rb)
		std::cout << (*rb).second << ' ';
	std::cout << std::endl;


	//--test;

	//std::cout << "--End: " << test->first << std::endl;


//	std::cout << "Len: " << (v1.end() - v1.begin()) << std::endl; 
	
	//test_vector<vector>(v);
	//modifyContent(v.begin(), v.end());
}