/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 08-03-2022  by  `-'                        `-'                  */
/*   Updated: 09-03-2022 16:22 by                                             */
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

	tree.insert(30);
	tree.insert(12);
	tree.insert(15);
	
	tree.insert(20);
	tree.insert(10);
	tree.insert(30);
	tree.insert(15);
	tree.insert(5);

	tree.insert(25);

	tree.insert(120);
	tree.insert(110);
	tree.insert(130);
	tree.insert(115);
	tree.insert(125);

	tree.insert(12);
	tree.insert(11);
	tree.insert(13);
	tree.insert(118);
	tree.insert(1202);




	//tree.insert(330);
	//tree.insert(312);
	//tree.insert(315);
	//tree.insert(320);
	//tree.insert(310);
	//tree.insert(330);
	//tree.insert(315);
	//tree.insert(35);
	//tree.insert(325);
	//tree.insert(3120);
	//tree.insert(3110);
	//tree.insert(3130);
	//tree.insert(3115);
	//tree.insert(3125);
	//tree.insert(312);
	//tree.insert(311);
	//tree.insert(313);
	//tree.insert(3118);
	//tree.insert(31202);
	tree.printTree("", tree.getRoot());

	search_val(tree, 12);
	search_val(tree, 20);
	search_val(tree, 10);
	search_val(tree, 30);
	search_val(tree, 15);
	search_val(tree, 25);
	search_val(tree, 26);

	std::cout << "AFTER REMOVAL\n\n\n";
	tree.remove(1202);
	tree.remove(125);
	tree.remove(12);
	tree.remove(20);

	tree.printTree("", tree.getRoot());
	
	search_val(tree, 12);
	search_val(tree, 20);
	search_val(tree, 10);
	search_val(tree, 30);
	search_val(tree, 15);
	search_val(tree, 25);
	search_val(tree, 26);
}