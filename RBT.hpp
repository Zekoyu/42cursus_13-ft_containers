/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 07-03-2022  by  `-'                        `-'                  */
/*   Updated: 09-03-2022 16:09 by                                             */
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
		node_pointer createNode(T value) /* Non-static since T is template dependant */
		{
			node_pointer node = new(RBNode<T>);

			node->color = RED;
			node->data = value;
			node->left = nullptr;
			node->parent = nullptr;
			node->right = nullptr;

			return (node);
		}

		void deleteNode(node_pointer node) /* Non-static since T is template dependant */
		{
			delete node;
		}


		/* See https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/ */
		/* https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp */

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

		/* As the name says, fix all violations, takes the newly added node, all the way up */
		void fixInsertionViolations(node_pointer k)
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
		}

		void fixDeleteViolations(node_pointer x)
		{
			node_pointer s = nullptr;

			while (x != this->_root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK)
						{
							s->left->color = BLACK;
							s->color = RED;
							rightRotate(s);
							s = x->parent->right;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->right->color = BLACK;
						leftRotate(x->parent);
						x = this->_root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED)
					{
						s->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->left->color == BLACK && s->right->color == BLACK)
					{
						s->color = RED;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK)
						{
							s->right->color = BLACK;
							s->color = RED;
							leftRotate(s);
							s = x->parent->left;
						}

						s->color = x->parent->color;
						x->parent->color = BLACK;
						s->left->color = BLACK;
						rightRotate(x->parent);
						x = this->_root;
					}
				}
			}
			x->color = BLACK;
		}

		void replaceNode(node_pointer node, node_pointer replacement)
		{
			/* Parent now points to replacement */
			if (node == this->_root)
				this->_root = replacement;
			else if (node == node->parent->left)
				node->parent->left = replacement;
			else
				node->parent->right = replacement;

			/* Replacement parent now points node parent */
			if (replacement != nullptr)
				replacement->parent = node->parent;
		}
		
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

		void remove(node_pointer node)
		{
			if (node == nullptr)
				return ;

			int originalColor = node->color;
			node_pointer newNode = nullptr;
			
			/* If node is a leaf, delete it from the tree */
			if (node->left == nullptr && node->right == nullptr)
				replaceNode(node, nullptr);
			else if (node->right == nullptr) /* Node has only one child (left) => replace node by it's left child */
			{
				newNode = node->left;
				replaceNode(node, node->left);
			}
			else if (node->left == nullptr) /* Node has only one child (right) */
			{
				newNode = node->right;
				replaceNode(node, node->right);
			}
			else /* Node has both child */
			{
				/* Find inorder successor of node (which basically in our case is the smallest value on root right subtree).
				   when found, it will replace the node */
				node_pointer successor = node->right;
				while (successor->left != nullptr)
					successor = successor->left;

				originalColor = successor->color;
				
				newNode = successor->right;

				if (successor->parent != node)
				{
					replaceNode(successor, successor->right);
					successor->right = node->right;
					successor->right->parent = node->right;
				}

				replaceNode(node, successor);
				successor->left = node->left;
				successor->left->parent = successor;
				successor->color = node->color;
			}
			
			this->deleteNode(node);
			if (originalColor == BLACK)
				this->fixDeleteViolations(newNode);
		}
		
		void remove(T val)
		{
			node_pointer node = this->search(val);

			if (node != nullptr)
				this->remove(node);
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