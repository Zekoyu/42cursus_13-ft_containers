/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 15-03-2022 19:38 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include "iterators.hpp"

#include <memory>
#include <functional>

#define BLACK 0
#define RED 1

namespace ft
{
	// RedBlackTree class with iterator, can only store UNIQUE values
	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RedBlackTree
	{
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef ptrdiff_t	difference_type;
			typedef size_t		size_type;

			typedef Compare data_compare;

		public:
			struct node
			{
				node* parent;
				node* left;
				node* right;

				value_type data;

				bool color;

				node() : parent(NULL), left(NULL), right(NULL), data(), color(RED) { }
				node(reference val) : parent(NULL, left(NULL), right(NULL), data(val), color(RED) { }
				node(const node& n) : parent(n.parent), left(n.left), right(n.right), data(n.data), color(n.color) { }
			};

		private:
			typedef node* node_pointer;
			typedef std::allocator<node> node_allocator_type;

			allocator_type		_alloc; // To allocate T
			node_allocator_type	_nodeAlloc; // To allocate new node
			data_compare		_comp; // To compare data for insertion / deletion / search
	
			node_pointer _root;
			node_pointer _dummyEnd; // Dummy end for end() iterator
			

			// Not static since it's type dependant
			node_pointer createNode(const value_Type& value = value_Type()) const
			{
				// Allocate a node but don't call constructor, so that we can construct T with T's alllocator
				node_pointer newNode = this->_nodeAlloc.allocate(1);

				// Construct the data directly with value, instead of calling default constructor then assigning
				this->_alloc.construct(&(newNode->data), value);

				newNode->parent = NULL;
				newNode->left = NULL;
				newNode->right = NULL;
				newNode->color = RED;

				return (newNode);
			}

			void deleteNode(node_pointer node)
			{
				if (node == NULL)
					return;

				// Only special case of deletion is when we delete the root
				// because it's the only node we keep track off, reset it when destroyed
				if (node == this->_root)
					this->_root = NULL;

				// Call destructor on the data
				this->_alloc.destroy(&(node->data));

				// Since nothing else need to be manually destroyed, just deallocate
				this->_nodeAlloc.deallocate(node, 1);
			}

			// See https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
			// https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/red-black-trees/RedBlackTree.cpp
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

				// Switch Y.left and X.right
				node->left = newNode->right;			// Y.left = b
				if (newNode->right != NULL)
					newNode->right->parent = node;		// b.parent = Y (to complete Y.left = b)

				// Redirect old links from X to Y
				newNode->parent = node->parent;			// X.parent = Y.parent (since we switch X and Y)
				if (node->parent == NULL)				// node is the root (same as node == this->_root)
					this->_root = newNode;				// root = X
				else if (node == node->parent->right)	// Y is the right child
					node->parent->right = newNode;		// Modify parent to point to X
				else									// Y is the left child
					node->parent->left = newNode;		// Modify parent to point to X

				// Change links between X and Y
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

				// Switch X.right and Y.left
				node->right = newNode->left;			// Y.left = b
				if (newNode->left != NULL)
					newNode->left->parent = node;		// b.parent = Y (to complete Y.left = b)

				// Redirect old links from X to Y
				newNode->parent = node->parent;			// X.parent = Y.parent (since we switch X and Y)
				if (node->parent == NULL)				// node is the root (same as node == this->_root)
					this->_root = newNode;				// root = X
				else if (node == node->parent->left)	// Y is the left child
					node->parent->left = newNode;		// Modify parent to point to X
				else									// Y is the left child
					node->parent->right = newNode;		// Modify parent to point to X

				// Change links between X and Y
				newNode->left = node;					// X.right = Y
				node->parent = newNode;					// Y.parent = X
			}

			// As the name says, fix all violations, takes the newly added node, all the way up
			void fixInsertionViolations(node_pointer node)
			{
				node_pointer	uncle;

				// Start from newly inserted node all the way up, since we put parent RED each time
				while (node->parent->color == RED)
				{
					if (node->parent == node->parent->parent->right) // Node parent is the right node of grand-parent 
					{
						uncle = node->parent->parent->left;
						if (uncle && uncle->color == RED) // Uncle red, switch colors
						{
							uncle->color = BLACK;
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else // Uncle black, set parent black and grand-parent red and rotate
						{
							if (node == node->parent->left)
							{
								node = node->parent; // parent will re-become child after rotate
								rightRotate(node);
							}
							node->parent->color = BLACK;		// This still be parent after left rotate, so make it black since node is red
							node->parent->parent->color = RED;	// Grand-parent will become sibling, so make it red since node is red
							leftRotate(node->parent->parent);
						}
					}
					else // Node parent is the left node of grand-parent => mirror scenario
					{
						uncle = node->parent->parent->right;
						if (uncle && uncle->color == RED) // Uncle red, switch colors
						{
							uncle->color = BLACK;
							node->parent->color = BLACK;
							node->parent->parent->color = RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent; // parent will re-become child after rotate
								leftRotate(node);
							}
							node->parent->color = BLACK;		// This still be parent after left rotate, so make it black since node is red
							node->parent->parent->color = RED;	// Grand-parent will become sibling, so make it red since node is red

							rightRotate(node->parent->parent);
						}
					}
					if (node == this->_root)
						break;
				}
				this->_root->color = BLACK;
			}

			void fixDeleteViolations(node_pointer node)
			{
				if (node == NULL)
					return;
					
				node_pointer sibling = NULL;
				while (node != this->_root && node->color == BLACK)
				{
					if (node == node->parent->left)
					{
						sibling = node->parent->right;
						if (sibling->color == RED)
						{
							sibling->color = BLACK;
							node->parent->color = RED;
							leftRotate(node->parent);
							sibling = node->parent->right;
						}

						if (sibling->left->color == BLACK && sibling->right->color == BLACK)
						{
							sibling->color = RED;
							node = node->parent;
						}
						else
						{
							if (sibling->right->color == BLACK)
							{
								sibling->left->color = BLACK;
								sibling->color = RED;
								rightRotate(sibling);
								sibling = node->parent->right;
							}

							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->right->color = BLACK;
							leftRotate(node->parent);
							node = this->_root;
						}
					}
					else
					{
						sibling = node->parent->left;
						if (sibling->color == RED)
						{
							sibling->color = BLACK;
							node->parent->color = RED;
							rightRotate(node->parent);
							sibling = node->parent->left;
						}

						if (sibling->left->color == BLACK && sibling->right->color == BLACK)
						{
							sibling->color = RED;
							node = node->parent;
						}
						else
						{
							if (sibling->left->color == BLACK)
							{
								sibling->right->color = BLACK;
								sibling->color = RED;
								leftRotate(sibling);
								sibling = node->parent->left;
							}
							
							sibling->color = node->parent->color;
							node->parent->color = BLACK;
							sibling->left->color = BLACK;
							rightRotate(node->parent);
							node = this->_root;
						}
					}
				}
				node->color = BLACK;
			}

			// replaces `node` with `replace`
			void replaceNode(node_pointer node, node_pointer replace)
			{
				// Make node parent point to replace
				if (node == this->_root)
					this->_root = replace;
				else if (node = node->parent->left)
					node->parent->left = replace;
				else
					node->parent->right = replace;

				// Make replace point to node parent
				if (replace != NULL)
					replace->parent = node->parent;
			}

			// Size is the size of left tree + 1 (Parent) + size of right tree
			size_type recursiveSize(node_pointer node) const
			{
				if (node == NULL)
					return (0);
				return (recursiveSize(node->left) + 1 + recursiveSize(node->right));
			}

			// Clears the tree from left to right, from leaves to root
			void recursiveClear(node_pointer node)
			{
				if (node == NULL)
					return;

				recursiveClear(node->left);
				recursiveClear(node->right);

				this->deleteNode(node);
			}

			node_pointer inorderSuccessor(node_pointer node)
			{
				if (node == NULL)
					return (NULL);

				// If node has a right child, successor is the smallest value of it's right subtree
				if (node->right != NULL)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				else
				{
					// In this case the node is on the furthest right of it's subtree,
					// go up until we find a node that is a left child, successor is this node's parent
					while (node->parent != NULL && node == node->parent->right)
						node = node->parent;
					node = node->parent;
				}

				return (node);
			}

			// Basically a mirror of inorderSuccessor
			node_pointer inorderPredecessor(node_pointer node)
			{
				if (node == NULL)
					return (NULL);

				// If node has a left child, predecessor is the biggest value of it's left subtree
				if (node->left != NULL)
				{
					node = node->left;
					while (node->right)
						node = node->right;
				}
				else
				{
					// In this case the node is on the furthest left of it's subtree
					// go up until we find a node that is a right child, predecessor is this node's parent
					while (node->parent != NULL && node == node->parent->right)
						node = node->parent;
					node = node->parent;
				}

				return (node);
			}


			// Pretty easy but I'm smartn't so this won't have my monkey brain
			bool isInf(const value_type& lhs, const value_type& rhs) const
			{ return (this->_comp(lhs, rhs)); }

			bool isInfOrEqual(const value_Type& lhs, const value_type& rhs) const
			{ return (this->isInf(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isSup(const value_type& lhs, const value_type& rhs) const
			{ return (!this->isInferior(lhs, rhs) && !this->isEqual(lhs, rhs)); }

			bool isSupOrEqual(const value_Type& lhs, const value_type& rhs) const
			{ return (this->isSup(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isEq(const value_type& lhs, const value_type& rhs) const
			{ return (!this->_comp(lhs, rhs) && !this->_comp(rhs, lhs)); }

		public:
			RedBlackTree(const data_compare& comp = data_compare(),
			       const allocator_type& alloc = allocator_type())
				   : _comp(comp), _alloc(alloc), _nodeAlloc(), _root(NULL), _dummyEnd(NULL)
			{
				this->_dumyEnd = this->createNode();
			}

			~RedBlackTree()
			{ this->clear; this->deleteNode(this->_dummyEnd); }

			// Returns true if value was inserted, false if some was already there
			bool insert(const value_type& val)
			{
				node_pointer node = this->createNode(val);

				if (this->_root == NULL)
				{
					node->color = BLACK;
					this->_root = node;
					return;
				}

				node_pointer curr = this->_root;
				node_pointer parent = NULL;

				while (curr != NULL)
				{
					parent = curr;
					if (isInf(node->data, curr->data))
						node = node->left;
					else if (isSup(node->data, curr->data))
						node = node->right;
					else // Same value already present
						return (false);
				}

				node->parent = parent;
				if (isInf(node->data, parent->data))
					parent->left = node;
				else
					parent->right = node;

				this->fixInsertionViolations(node);

				return (true);
			}

			void remove(node_pointer node)
			{
				if (node == NULL)
					return;

				int originalColor = node->color;
				node_pointer newNode = NULL;

				if (node->left == NULL && node->right == NULL)
				{
					// If node is a leaf, just remove it from the tree
					this->replaceNode(node, NULL);
				}
				else if (node->right == NULL)
				{
					// Node only has a left child, just make it's child become the new node
					newNode = node->left;
					replaceNode(node, node->left);
				}
				else if (node->left == NULL)
				{
					// Node only has a right child, just make it's child become the new node
					newNode = node->right;
					replaceNode(node, node->right);
				}
				else
				{
					// Node has 2 childs, find inorder successor, which will replace the node
					node_pointer successor = this->inorderSuccessor(node);
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

			void remove(const valule_type& val) { this->remove(this->search(val)); }			

			node_pointer search(const value_Type& val) const
			{
				if (this->_root == NULL || (this->isEq(val, this->_root->data)))
					return (this->_root);

				node_pointer curr = this->_root;

				while (curr != NULL && !this->isEq(val, curr->data))
				{
					if (isInf(val, curr->data))
						curr = curr->left;
					else
						curr = curr->right;
				}
				return (curr); // Either a isEq(ual) node or NULL
			}

			node_pointer getRoot() const { return (this->_root); }

			size_t size() const { return (this->recursiveSize(this->_root)); }

			void clear() { this->recursiveClear(this->_root); this->_root = NULL }

	};

}

#endif