/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 13-03-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 12:05 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "VectorIterator.hpp"
#include <iostream>
#include <vector>

int main()
{
	typedef int TYPE;

	typedef ft::VectIterator<TYPE, false> it;
	typedef ft::VectIterator<TYPE, true>  cit;


	typedef std::vector<TYPE>::iterator vit;
	typedef std::vector<TYPE>::const_iterator vcit;

	it it1;
	it it2;
	cit cit1;
	cit cit2;

	vit vit1;
	vit vit2;	
	vcit vcit1;
	vcit vcit2;

	// it1 = it2;
	// cit1 = cit2;

	// vit1 = vit2;
	// vcit1 = vcit2;

	// cit1 = it1;
	// vcit1 = vit1;

	it add = 1 + it2;
	it add2 = it2 + 1;

	cit1++;

	(void) add;
	(void) add2;


	std::cout << (vit1 == vcit2) << std::endl;
	std::cout << (vit1 != vcit2) << std::endl;
	std::cout << (vit1 <  vcit2) << std::endl;
	std::cout << (vit1 <= vcit2) << std::endl;
	std::cout << (vit1 >  vcit2) << std::endl;
	std::cout << (vit1 >= vcit2) << std::endl;
	//std::cout << *it1 << std::endl;


	std::vector<int> test;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);

	std::cout << "First elt is " << test[0] << std::endl;
	std::cout << "erase result: " << *(test.erase(test.begin(), test.begin())) << std::endl;
	std::cout << "First elt is " << test[0] << std::endl;

}