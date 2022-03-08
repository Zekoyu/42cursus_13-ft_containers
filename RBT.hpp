/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 07-03-2022  by  `-'                        `-'                  */
/*   Updated: 08-03-2022 22:16 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <functional>
#include <iostream>

enum e_color
{
	BLACK,
	RED
};

template <class T>
struct RBNode
{
	RBNode	*parent;
	RBNode	*right;
	RBNode	*left;

	T		data;
	
	e_color	color;
};

/* https://en.wikipedia.org/wiki/Red%E2%80%93black_tree */
/* PROPERTIES:
	- The root node should always be black in color.
	- Every null child of a node is black in red black tree.
	- The children of a red node are black. It can be possible that parent of red node is black node. (No red nodes can be adjacent)
	- All the leaves have the same black depth.
	- Every simple path from the root node to the (downward) leaf node contains the same number of black nodes.

	RBT operations are guaranteed to be O(log n)
	Red Black Tree is a self balancing Binary Search Tree

	https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
*/
template <class T, class Compare = std::less<T> >
class RBTree
{
	public:
		typedef RBNode<T>*	node_pointer;

	private:
		RBNode<T>*	_root;

	private:

		/* Nodes are red by default to not violate black depth property,
		and it's easier to fix wrong red nodes than to find where to create black nodes */
		node_pointer createNode(T value)
		{
			node_pointer node = new(RBNode<T>);

			node->color = RED;
			node->data = value;
			node->left = nullptr;
			node->parent = nullptr;
			node->right = nullptr;

			return (node);
		}
		
		/* Returns new root of subtree */
		/* Will rotate using node as root and node child as pivot,
		makes root pivot child (root.left) is now root and (new_root).right is now base root */
		node_pointer rotateRight(node_pointer root)
		{
			node_pointer	parent = root->parent;
			node_pointer	pivot = root->left;
			node_pointer	rightChild;

			if (pivot == nullptr)
				return nullptr;
			
			rightChild = pivot->right;

			root->left = rightChild;
			if (rightChild != nullptr)
				rightChild->parent = root;

			pivot->right = root;
			root->parent = pivot;

			pivot->parent = parent;

			/* Set the new root to be pivot */
			if (parent == nullptr)
				this->_root = pivot;
			else if (pivot == parent->left)
				parent->left = pivot;
			else
				parent->right = pivot;

			return (pivot); /* Return new root */	
		}

		/*
		node_pointer rotateLeft(node_pointer root)
		{
			node_pointer	parent = root->parent;
			node_pointer	pivot = root->right;
			node_pointer	leftChild;

			if (pivot == NULL)
				return NULL;
			
			leftChild = pivot->left;

			root->right = leftChild;
			if (leftChild != NULL)
				leftChild->parent = root;

			pivot->left = root;
			root->parent = pivot;

			if (parent == NULL)
			{
				this->_root = pivot;
				return (this->_root);
			}
			else if (pivot == parent->left)
				parent->left = pivot;
			else
				parent->right = pivot;
			pivot->parent = parent;

			return (pivot);	
		}*/

		void rotateLeft(node_pointer x) {
            node_pointer nw_node = createNode(x->data);
            if(x->right->left) { nw_node->right = x->right->left; }
            nw_node->left = x->left;
            nw_node->data = x->data;
            nw_node->color = x->color;
            x->data = x->right->data;

            x->left = nw_node;
            if(nw_node->left){ nw_node->left->parent = nw_node; }
            if(nw_node->right){ nw_node->right->parent = nw_node; }
            nw_node->parent = x;

            if(x->right->right){ x->right = x->right->right; }
            else { x->right = nullptr; }

            if(x->right){ x->right->parent = x; }
        }


		/* As the name says, fix all violations, takes the newly added node */
		/* See https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/ */

		
		//https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp

		/* Rotate node n right, makes it become the child and it's left child the parent 
		   
		   rightRotate(Y) does:
		      Y           X      
		     / \    >    / \      
		    X   c   >   a   Y     
		   / \      >      / \    
		  a   b           b   c   
		  Before         After

		  Things that change are:
		  - Y.left is now X.right
		  - X.right is now Y
		  - X.parent is now old Y.parent and
		    Y.parent is now X
		*/
		void rightRotate(node_pointer node)
		{
			node_pointer newNode = node->left;		// new parent = X
			/* Switch Y.left and X.right */
			
			node->left = newNode->right;			// Y.left = b
			if (newNode->right != nullptr)
				newNode->right->parent = node;		// b.parent = Y (to complete Y.left = b)
			/* Redirect old links from X to Y */
			newNode->parent = node->parent;			// X.parent = Y.parent (since we switch X and Y)
			if (node->parent == nullptr)				// node is the root (same as node == this->_root)
				this->_root = newNode;				// root = X
			else if (node == node->parent->right)	// Y is the right child
				node->parent->right = newNode;		// Modify parent to point to X
			else									// Y is the left child
				node->parent->left = newNode;		// Modify parent to point to X
			/* Change links between X and Y */
			newNode->right = node;					// X.right = Y
			node->parent = newNode;					// Y.parent = X
		}

		/* Rotate node n left, makes it become the child and it's right child the parent 
		   
		   leftRotate(X) does:
			X               Y
		   / \      >      / \
		  a   Y     >     X   c
		     / \    >    / \
			b   c       a   b
		  Before         After

		   Things that change are:
		  - X.right is now Y.left
		  - Y.left is now x
		  - X.parent is now old Y.parent and
		    Y.parent is now X
		*/
		void leftRotate(node_pointer node)
		{
			node_pointer newNode = node->right;		// new parent = X
			/* Switch X.right and Y.left */
			node->right = newNode->left;			// Y.left = b
			if (newNode->left != nullptr)
				newNode->left->parent = node;		// b.parent = Y (to complete Y.left = b)
			/* Redirect old links from X to Y */
			newNode->parent = node->parent;			// X.parent = Y.parent (since we switch X and Y)
			if (node->parent == nullptr)				// node is the root (same as node == this->_root)
				this->_root = newNode;				// root = X
			else if (node == node->parent->left)	// Y is the left child
				node->parent->left = newNode;		// Modify parent to point to X
			else									// Y is the left child
				node->parent->right = newNode;		// Modify parent to point to X
			/* Change links between X and Y */
			newNode->left = node;					// X.right = Y
			node->parent = newNode;					// Y.parent = X
		}

		void	fixInsertionViolations(node_pointer k)
		{
			node_pointer	uncle;

			/* Start from newly inserted node all the way up, since we put parent RED each time */
			while (k->parent->color == RED)
			{
				if (k->parent == k->parent->parent->right) /* Node parent is the right node of grand-parent */
				{
					uncle = k->parent->parent->left;
					if (uncle && uncle->color == RED) /* Uncle red, switch colors */
					{
						uncle->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else /* Uncle black, set parent black and grand-parent red and rotate */
					{
						if (k == k->parent->left)
						{
							k = k->parent; /* parent will re-become child after rotate */
							rightRotate(k);
						}
						k->parent->color = BLACK;		/* This still be parent after left rotate, so make it black since node is red */
						k->parent->parent->color = RED;	/* Grand-parent will become sibling, so make it red since node is red */
						leftRotate(k->parent->parent);
					}
				}
				else /* Node parent is the left node of grand-parent => mirror scenario */
				{
					
					uncle = k->parent->parent->right;
					if (uncle && uncle->color == RED) /* Uncle red, switch colors */
					{
						uncle->color = BLACK;
						k->parent->color = BLACK;
						k->parent->parent->color = RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent; /* parent will re-become child after rotate */
							leftRotate(k);
						}
						k->parent->color = BLACK;		/* This still be parent after left rotate, so make it black since node is red */
						k->parent->parent->color = RED;	/* Grand-parent will become sibling, so make it red since node is red */

						rightRotate(k->parent->parent);
					}
				}
				if (k == this->_root)
					break;
			}
			this->_root->color = BLACK;
			/*
					30
				   /
				 12
				  \
				   15

				 30
				 /
				15
			   /
			  12 
			*/
		}
		
		/* Strategy is to start from the node all the way up to the root */
		// V2
		// void	fixRBTProperties(node_pointer n)
		// {
		// 	node_pointer	grandParent = NULL;
		// 	node_pointer	uncle = NULL;

		// 	while (n->parent->color == RED)
		// 	{
		// 		grandParent = n->parent->parent;
		// 		uncle = NULL;

		// 		if (n->parent == grandParent->left) /* Parent is left child of grandparent */
		// 		{
		// 			if (grandParent->right != NULL) /* If grandparent has another child, it's the node uncle */
		// 				uncle = grandParent->right;
					
		// 			if (uncle != NULL && uncle->color == RED) /* If uncle is red, switch colors */
		// 			{
		// 				n->parent->color = BLACK;
		// 				uncle->color = BLACK;
		// 				grandParent->color = RED;
		// 				if (grandParent != this->_root)
		// 					n = grandParent;
		// 				else /* We finished our loop, we reached the top */
		// 					break;
		// 			}
		// 			else if (n == grandParent->left->right) /* Node is Right child of parent */
		// 			{
		// 				rotateLeft(n->parent);
		// 			}
		// 			else /* Node is red child of parent */
		// 			{
		// 				n->parent->color = BLACK;
		// 				grandParent->color = RED;
		// 				rotateRight(grandParent);
		// 				if (grandParent != this->_root)
		// 					n = grandParent; /* Up one node */
		// 				else
		// 					break ;
		// 			}
		// 		}
		// 		else /* Parent is grandparent right child */
		// 		{
		// 			if (grandParent->left != NULL) /* If grandparent has another child, it's the node uncle */
		// 				uncle = grandParent->left;
					
		// 			if (uncle != NULL && uncle->color == RED) /* If uncle is red, switch colors */
		// 			{
		// 				n->parent->color = BLACK;
		// 				uncle->color = BLACK;
		// 				grandParent->color = RED;
		// 				if (grandParent != this->_root)
		// 					n = grandParent;
		// 				else /* We finished our loop, we reached the top */
		// 					break;
		// 			}
		// 			else if (n == grandParent->right->left) /* Node is left child of parent */
		// 			{
		// 				rotateRight(n->parent);
		// 			}
		// 			else /* Node is red child of parent */
		// 			{
		// 				n->parent->color = BLACK;
		// 				grandParent->color = RED;
		// 				rotateLeft(grandParent);
		// 				if (grandParent != this->_root)
		// 					n = grandParent; /* Up one node */
		// 				else
		// 					break ;
		// 			}
		// 		}
		// 	}
		// 	this->_root->color = BLACK; /* Since we rotated, set black just in case */
		// }

		// void fixRBTProperties(node_pointer node)
		// {
		//  	node_pointer	parent = node->parent;
		//  	node_pointer	grandParent = parent != NULL ? parent->parent : NULL;
		//  	node_pointer	uncle = grandParent != NULL ? (parent == grandParent->left ? grandParent->right : grandParent->left) : NULL;

		// 	/* Case 1: Tree is empty => node is the new root, it should therefore be black */
		// 	if (this->_root == NULL)
		// 	{
		// 		node->color = BLACK;
		// 		this->_root = node;
		// 		return;
		// 	}

		// 	/* Case 2: Parent is black => Don't do anything
		// 	   (since parent is black, before our new node it was already balanced, adding the red node does not break the black depth property) */
		// 	if (parent->color == BLACK)
		// 		return;
			
		// 	/* Case 3 : Parent is red => Violation of "no 2 red nodes adjacent" property */
		// 	if (parent->color == RED)
		// 	{
		// 		uncle = grandParent != NULL ? (parent == grandParent->left ? grandParent->right : grandParent->left) : NULL;
		// 		/* Case 3.1: Parent is red and Uncle too: flip Parent, Uncle and GrandParent colors, if GP is root, switch it back to black */
		// 		if (uncle->color == RED)
		// 		{
		// 			parent->color = BLACK;
		// 			uncle->color = BLACK;
		// 			if (grandParent != this->_root)
		// 				grandParent->color = RED;

		// 			node = node->parent
		// 			continue;
		// 		}
		// 		/* Case 3.2: Parent is red and Uncle is black/NULL */
		// 		else
		// 		{
		// 			/* Cases 3.2.1 / 3.2.2: Parent is right child of GrandParent */
		// 			if (parent == grandParent->right)
		// 			{
						
		// 				if (node == parent->right) /* Case 3.2.2: Node is to the left of parent => right rotate parent then it's same case */
		// 					rotateRight(parent);

		// 				/* Case 3.2.1: Node is to the right of Parent => Left-rotate grandParent (Node sibling is now grandParent)
		// 				   new parent = black, new sibling = red */
		// 				rotateLeft(grandParent); /* grandParent is the same when child is left or right of parent */
		// 				parent->color = BLACK; /* Parent is still parent */
		// 				grandParent->color = RED; /* grandParent is now sibling */
						
		// 			}
		// 			/* Cases 3.2.3 / 3.2.4: Parent is left child of GrandParent */
		// 			else
		// 			{
		// 				/* Case 3.2.3: Node is to the left of Parent => mirror of 3.2.1 */
		// 				if (node == parent->left)
		// 					rotateLeft(parent);

		// 				/* Case 3.2.4: Node is to the right of Parent => mirror of 3.2.2 */
		// 				rotateRight(grandParent);
		// 				parent->color = BLACK;
		// 				grandParent->color = RED;
		// 			}
		// 		}

		// 		return;
		// 	}


			

		// 	/* Start from newly inserted node all the way up to root */
		// 	while ((node != this->_root) && (node->color != BLACK) &&
		// 			(node->parent->color == RED))
		// 	{

		// 		parent = node->parent;
		// 		grandParent = node->parent->parent; /* We know there is always a grandparent because if parent == BLACK (root is always black) we don't enter it */

		// 		/*  Case : A
		// 			Parent of pt is left child
		// 			of Grand-parent of pt */
		// 		if (parent == grandParent->left)
		// 		{

		// 			uncle = grandParent->right;

		// 			/* Case : 1
		// 				The uncle of pt is also red
		// 				Only Recoloring required */
		// 			if (uncle != NULL && uncle->color == RED)
		// 			{
		// 				grandParent->color = RED;
		// 				parent->color = BLACK;
		// 				uncle->color = BLACK;
		// 				node = grandParent;
		// 			}

		// 			else
		// 			{
		// 				/* Case : 2
		// 					pt is right child of its parent
		// 					Left-rotation required */
		// 				if (node == parent->right)
		// 				{
		// 					rotateLeft(root, parent);
		// 					node = parent;
		// 					parent = node->parent;
		// 				}

		// 				/* Case : 3
		// 					pt is left child of its parent
		// 					Right-rotation required */
		// 				rotateRight(root, grandParent);
		// 				swap(parent->color, grandParent->color);
		// 				node = parent;
		// 			}
		// 		}

		// 		/* Case : B
		// 			Parent of pt is right child
		// 			of Grand-parent of pt */
		// 		else /* Parent is on the left of grandparent*/
		// 		{
		// 			uncle = grandParent->left;

		// 			/*  Case : 1
		// 				The uncle of pt is also red
		// 				Only Recoloring required */
		// 			if ((uncle != NULL) && (uncle->color == RED))
		// 			{
		// 				grandParent->color = RED;
		// 				parent->color = BLACK;
		// 				uncle->color = BLACK;
		// 				node = grandParent;
		// 			}
		// 			else
		// 			{
		// 				/* Case : 2
		// 					pt is left child of its parent
		// 					Right-rotation required */
		// 				if (node == parent->left)
		// 				{
		// 					rotateRight(root, parent);
		// 					node = parent;
		// 					parent = node->parent;
		// 				}

		// 				/* Case : 3
		// 					pt is right child of its parent
		// 					Left-rotation required */
		// 				rotateLeft(root, grandParent);
		// 				swap(parent->color,
		// 							grandParent->color);
		// 				node = parent;
		// 			}
		// 		}
		// 	}
		// 	root->color = BLACK;
		// }




	public:

		RBTree() : _root(nullptr) { }	// NULL is typically convertible to int, nullptr only to pointers

		/* Insert as in any Binary Search Tree, then fix the RBT violations if any */
		void insert(T val)
		{
			node_pointer node = createNode(val);

			if (this->_root == nullptr)
			{
				this->_root = node;
				node->color = BLACK;
				return;
			}

			node_pointer	curr_node = this->_root;
			node_pointer	parent = nullptr; /* this.roo.parent */
			
			Compare			comp;
			
			while (curr_node != nullptr)
			{
				parent = curr_node;
				if (comp(node->data, curr_node->data)) /* node < curr_node */
					curr_node = curr_node->left;
				else
					curr_node = curr_node->right;
			}

			/* Here curr_node is a leaf (NULL), and parent is the parent of that leaf */
			node->parent = parent; /* Set parent */
			if (comp(node->data, parent->data)) /* Set child */
				parent->left = node;
			else
				parent->right = node;

			/* No need to set color and childs since they should be initialized to NULL and RED */

			//this->fixRBTProperties(node);
			this->fixInsertionViolations(node);
		}

		node_pointer	search(T val)
		{
			if (this->_root == nullptr || this->_root->data == val)
				return (this->_root);

			node_pointer curr = this->_root;
			Compare comp;
			while (curr && curr->data != val)
			{
				if (comp(val, curr->data))
					curr = curr->left;
				else
					curr = curr->right;
			}
			return (curr); /* Either node / NULL */
		}

		void printTree(const std::string& prefix, node_pointer node, bool isLeft = false)
		{
			if( node != nullptr )
			{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );

				// print the value of the node
				std::cout << (node->color == RED ? "R" : "B") <<  node->data << std::endl;

				// enter the next tree level - left and right branch
				printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
				printTree( prefix + (isLeft ? "│   " : "    "), node->right, false);
			}
		}

		node_pointer getRoot() { return this->_root; }
};

#endif