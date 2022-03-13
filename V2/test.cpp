/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 13-03-2022  by  `-'                        `-'                  */
/*   Updated: 13-03-2022 14:37 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "RandIterator.hpp"
#include <iostream>
#include <vector>

int main()
{
	typedef int TYPE;

	typedef ft::RandIterator<TYPE, false> it;
	typedef ft::RandIterator<TYPE, true>  cit;

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

	it1 = it2;
	cit1 = cit2;

	vit1 = vit2;
	vcit1 = vcit2;

	cit1 = it1;
	vcit1 = vit1;

}