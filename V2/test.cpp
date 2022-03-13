/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 13-03-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 00:22 by                                             */
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


	std::vector<int> test(10);

	test[9] = 123;
	std::cout << "size is " << test.size() << std::endl;
	test.erase(test.begin() + 9);
	std::cout << "size is " << test.size() << std::endl;
	std::cout << test[9] << std::endl;

}