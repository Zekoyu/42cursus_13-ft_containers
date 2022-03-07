/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 07-03-2022  by  `-'                        `-'                  */
/*   Updated: 07-03-2022 22:40 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

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
	- The children of a red node are black. It can be possible that parent of red node is black node.
	- All the leaves have the same black depth.
	- Every simple path from the root node to the (downward) leaf node contains the same number of black nodes.

	RBT operations are guaranteed to be O(log n)
	Red Black Tree is a self balancing Binary Search Tree
*/
template <class T, class Compare>
class RBTree
{
	private:
		typedef RBNode<T>*	node_pointer;
		RBNode<T>*	_root;

	private:

		/* Nodes are red by default to not violate black depth property,
		and it's easier to fix wrong red nodes than to find where to create black nodes */
		template <class T>
		node_pointer createNode(T value)
		{
			node_pointer	node = new(RBNode<T>);

			node->color = RED;
			node->data = value;
			node->left = NULL;
			node->parent = NULL;
			node->right = NULL;

			return (node);
		}
		
		/* Returns new root of subtree */
		/* Will rotate using node as root and node child as pivot,
		makes root pivot child (root.left) is now root and (new_root).right is now base root */
		node_pointer rotateRight(node_pointer root)
		{
			node_pointer	parent = node->parent;
			node_pointer	pivot = node->left;
			node_pointer	rightChild;

			if (pivot == NULL)
				return NULL;
			
			rightChild = pivot->right;

			root->left = rightChild;
			if (rightChild != NULL)
				rightChild->parent = root;

			pivot->right = root;
			root->parent = pivot;

			pivot->parent = parent;

			/* Set the new root to be pivot */
			if (parent != NULL) /* If root node isn't the root of the whole tree */
				parent->right = pivot;
			else
				this->_root = pivot;

			return (pivot); /* Return new root */	
		}

		node_pointer rotateLeft(node_pointer root)
		{
			node_pointer	parent = node->parent;
			node_pointer	pivot = node->left;
			node_pointer	leftChild;

			if (pivot == NULL)
				return NULL;
			
			leftChild = pivot->left;

			root->left = leftChild;
			if (leftChild != NULL)
				leftChild->parent = root;

			pivot->left = root;
			root->parent = pivot;

			pivot->parent = parent;

			if (parent != NULL)
				parent->left = pivot;
			else
				this->_root = pivot;

			return (pivot);	
		}

		/* As the name says, fix all violations, takes the newly added node */
		void fixRBTProperties(node_pointer node)
		{
			node_pointer	parent = NULL;
			node_pointer	grandParent = NULL;
			node_pointer	uncle = NULL;

			/* Start from newly inserted node all the way up to root */
			while ((node != this->_root) && (node->color != BLACK) &&
					(node->parent->color == RED))
			{

				parent = node->parent;
				grandParent = node->parent->parent; /* We know there is always a grandparent because if parent == BLACK (root is always black) we don't enter it */

				/*  Case : A
					Parent of pt is left child
					of Grand-parent of pt */
				if (parent == grandParent->left)
				{

					uncle = grandParent->right;

					/* Case : 1
						The uncle of pt is also red
						Only Recoloring required */
					if (uncle != NULL && uncle->color == RED)
					{
						grandParent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						node = grandParent;
					}

					else
					{
						/* Case : 2
							pt is right child of its parent
							Left-rotation required */
						if (node == parent->right)
						{
							rotateLeft(root, parent);
							node = parent;
							parent = node->parent;
						}

						/* Case : 3
							pt is left child of its parent
							Right-rotation required */
						rotateRight(root, grandParent);
						swap(parent->color,
									grandParent->color);
						node = parent;
					}
				}

				/* Case : B
					Parent of pt is right child
					of Grand-parent of pt */
				else /* Parent is on the left of grandparent*/
				{
					uncle = grandParent->left;

					/*  Case : 1
						The uncle of pt is also red
						Only Recoloring required */
					if ((uncle != NULL) && (uncle->color == RED))
					{
						grandParent->color = RED;
						parent->color = BLACK;
						uncle->color = BLACK;
						node = grandParent;
					}
					else
					{
						/* Case : 2
							pt is left child of its parent
							Right-rotation required */
						if (node == parent->left)
						{
							rotateRight(root, parent);
							node = parent;
							parent = node->parent;
						}

						/* Case : 3
							pt is right child of its parent
							Left-rotation required */
						rotateLeft(root, grandParent);
						swap(parent->color,
									grandParent->color);
						node = parent;
					}
				}
			}
			root->color = BLACK;
		}

	public:
		/* Insert as in any Binary Search Tree, then fix the RBT violations if any */
		void insert(node_pointer node)
		{
			if (this->_root == NULL)
			{
				this->_root = node;
				return;
			}

			node_pointer	curr_node = this->_root;
			node_pointer	parent = NULL; /* this.roo.parent */
			
			Compare			comp;
			
			while (curr_node != NULL)
			{
				parent = curr_node;
				if comp(node->data, curr_node->data) /* node < curr_node */
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

			this->fixRBTProperties();
		}
};

#endif