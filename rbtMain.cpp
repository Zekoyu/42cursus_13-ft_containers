/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 08-03-2022  by  `-'                        `-'                  */
/*   Updated: 08-03-2022 17:31 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "RBT.hpp"
#include <iostream>

void search_val(RBTree<int> tree, int val)
{
	RBTree<int>::node_pointer node;

	node = tree.search(val);

	if (node != NULL)
		std::cout << "Found value " << val << std::endl;
	else
		std::cout << "Didn't found value " << val << std::endl;
}

int main()
{
	class RBTree<int> tree;

	tree.insert(20);
	tree.insert(10);
	tree.insert(30);
	tree.insert(15);
	tree.insert(25);

	search_val(tree, 12);
	search_val(tree, 20);
	search_val(tree, 10);
	search_val(tree, 30);
	search_val(tree, 15);
	search_val(tree, 25);
	search_val(tree, 26);
}