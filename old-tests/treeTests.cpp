/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 10:46 by                                             */
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

	pouet.clear();


	ft::map<char,int> mymap;
	ft::map<char,int>::iterator itlow,itup;


	// mymap['a']=20;
	// mymap['b']=40;
	// mymap['c']=60;
	// mymap['d']=80;
	// mymap['e']=100;

	mymap['b']=40;
	mymap['e']=100;
	mymap['d']=80;
	mymap['c']=60;
	mymap['a']=20;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)

	//while (1);

	//std::cout << "== ? " << (mymap.begin() == mymap.end()) << std::endl;
	// print content:
	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << std::endl;

	std::cout << "--end is " << (--(mymap.end()))->first << std::endl;
	std::cout << "begin is " << (mymap.begin())->first << std::endl;
	std::cout << "++begin is " << (++(mymap.begin()))->first << std::endl;
	std::cout << "++(++begin) == end ? " << (++(++(mymap.begin())) == mymap.end()) << std::endl;
}

