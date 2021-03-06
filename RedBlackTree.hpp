/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 15-03-2022  by  `-'                        `-'                  */
/*   Updated: 17-03-2022 22:37 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

#include "TreeIterator.hpp"

#include <memory>
#include <functional>
#include <iostream>

#define BLACK 0
#define RED 1

namespace ft
{
	// RedBlackTree class with iterator, can only store UNIQUE values
	template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T> >
	class RedBlackTree
	{
		private:
			typedef RedBlackTree<T, Compare, Allocator> self_type;

		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef TreeIterator<self_type, false>	iterator;
			typedef TreeIterator<self_type, true>	const_iterator;

			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

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
				node(reference val) : parent(NULL), left(NULL), right(NULL), data(val), color(RED) { }
				node(const node& n) : parent(n.parent), left(n.left), right(n.right), data(n.data), color(n.color) { }
			};

			typedef node* node_pointer;

		private:
			
			typedef std::allocator<node> node_allocator_type;

			allocator_type		_alloc; // To allocate T
			node_allocator_type	_nodeAlloc; // To allocate new node
			data_compare		_comp; // To compare data for insertion / deletion / search
	
			node_pointer _root;
			node_pointer _dummyEnd; // Dummy end for end() iterator
			

			// Not static since it's type dependant
			node_pointer createNode(const value_type& value = value_type())
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

			void createEndNode()
			{
				this->_dummyEnd = this->createNode();
				this->_dummyEnd->color = END_NODE_COLOR;
			}

			// Set the end node at the end of the tree
			void setEndNodeAtTheEnd()
			{
				node_pointer curr = this->_root;

				while (curr != NULL && curr->right)
					curr = curr->right;
				
				if (curr != NULL && curr->right != this->_dummyEnd)
					curr->right = this->_dummyEnd;
				//else
				//	this->_root = this->_dummyEnd;
				this->_dummyEnd->parent = curr;
			}

			// When seraching / inserting, hide the node from the tree
			void vanishEndNode()
			{
				if (this->_dummyEnd->parent != NULL)
					this->_dummyEnd->parent->right = NULL;
				this->_dummyEnd->parent = NULL;
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
				else if (node == node->parent->left)
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
				if (node == NULL || node == this->_dummyEnd)
					return (0);
				return (recursiveSize(node->left) + 1 + recursiveSize(node->right));
			}

			// Clears the tree from left to right, from leaves to root
			void recursiveClear(node_pointer node)
			{
				if (node == NULL || node == this->_dummyEnd)
					return;

				recursiveClear(node->left);
				recursiveClear(node->right);

				this->deleteNode(node);
			}

			// Pretty easy but I'm smartn't so this won't have my monkey brain
			bool isInf(const value_type& lhs, const value_type& rhs) const
			{ return (this->_comp(lhs, rhs)); }

			bool isInfOrEqual(const value_type& lhs, const value_type& rhs) const
			{ return (this->isInf(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isSup(const value_type& lhs, const value_type& rhs) const
			{ return (!this->isInf(lhs, rhs) && !this->isEq(lhs, rhs)); }

			bool isSupOrEqual(const value_type& lhs, const value_type& rhs) const
			{ return (this->isSup(lhs, rhs) || this->isEq(lhs, rhs)); }

			bool isEq(const value_type& lhs, const value_type& rhs) const
			{ return (!this->_comp(lhs, rhs) && !this->_comp(rhs, lhs)); }

		public:
			RedBlackTree(const data_compare& comp = data_compare(),
			    		 const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _nodeAlloc(), _comp(comp), _root(NULL), _dummyEnd(NULL)
			{
				this->createEndNode();
			}

			RedBlackTree(const self_type& tree)
			: _alloc(tree._alloc), _nodeAlloc(tree._nodeAlloc), _comp(tree._comp), _root(NULL), _dummyEnd(NULL)
			{
				this->createEndNode();
				for (const_iterator it = tree.begin(); it != tree.end(); ++it)
					this->insert(*it);
			}

			~RedBlackTree()
			{
				this->clear();

				this->deleteNode(this->_dummyEnd);
			}

			// https://stackoverflow.com/questions/3381867/iterating-over-a-map/3382702#3382702
			template <class Node>
			static node_pointer inorderSuccessor(Node* node)
			{
				if (node == NULL)
					return (NULL);

				// If node has a right child, successor is the smallest value of it's right subtree
				if (node->right != NULL)
				{
					node = node->right;
					while (node->left != NULL)
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
			template <class Node>
			static node_pointer inorderPredecessor(Node* node)
			{
				if (node == NULL)
					return (NULL);

				// If node has a left child, predecessor is the biggest value of it's left subtree
				if (node->left != NULL)
				{
					node = node->left;
					while (node->right != NULL)
						node = node->right;
				}
				else
				{
					// In this case the node is on the furthest left of it's subtree
					// go up until we find a node that is a left child, predecessor is this node's parent
					while (node->parent != NULL && node == node->parent->left)
						node = node->parent;
					node = node->parent;
				}
				
				return (node);
			}

			// Returns true if value was inserted, false if some was already there
			bool insert(const value_type& val)
			{
				node_pointer node = this->createNode(val);
				
				this->vanishEndNode();
				
				if (this->_root == NULL)
				{
					node->color = BLACK;
					this->_root = node;
					this->setEndNodeAtTheEnd();
					return (true);
				}

				node_pointer curr = this->_root;
				node_pointer parent = NULL;

				while (curr != NULL)
				{
					parent = curr;
					if (isInf(node->data, curr->data))
						curr = curr->left;
					else if (isSup(node->data, curr->data))
						curr = curr->right;
					else // Same value already present
					{
						this->setEndNodeAtTheEnd();
						return (false);
					}
				}
				node->parent = parent;
				if (isInf(node->data, parent->data))
					parent->left = node;
				else
					parent->right = node;

				this->fixInsertionViolations(node);
				
				this->setEndNodeAtTheEnd();
				return (true);
			}

			void remove(node_pointer node)
			{
				if (node == NULL)
					return;

				this->vanishEndNode();

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
						successor->right->parent = successor;
					}

					replaceNode(node, successor);
					successor->left = node->left;
					successor->left->parent = successor;
					successor->color = node->color;
				}

				this->deleteNode(node);
				if (originalColor == BLACK)
					this->fixDeleteViolations(newNode);
				
				this->setEndNodeAtTheEnd();
			}

			void remove(const value_type& val) { this->remove(this->search(val)); }			

			node_pointer search(const value_type& val) const
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

				if (curr == this->_dummyEnd)
					return (NULL);

				return (curr); // Either a isEq(ual) node or NULL
			}

			const node_pointer getRoot() const { return (this->_root); }

			const node_pointer getDummyEnd() const { return (this->_dummyEnd); }

			size_t size() const { return (this->recursiveSize(this->_root)); }

			void clear() {
				this->recursiveClear(this->_root);
				
				// Set parent to null in case we refill the tree after clear
				this->_dummyEnd->parent = NULL;

				this->_root = NULL;
			}

			node_pointer first() const
			{
				node_pointer curr = this->_root;

				while (curr != NULL && curr->left)
					curr = curr->left;
				return (curr);
			}

			node_pointer last() const
			{
				node_pointer curr = this->_root;

				while (curr != NULL && curr->right && curr->right != this->_dummyEnd)
					curr = curr->right;
				return (curr); 
			}

			iterator begin()
			{
				node_pointer val = this->first();

				if (val == NULL)
					return (this->end());
				return (iterator(val));
			}		

			const_iterator begin() const
			{
				node_pointer val = this->first();

				if (val == NULL)
					return (this->end());
				return (const_iterator(val));
			}

			iterator		end() {return (iterator(this->_dummyEnd)); }
			const_iterator	end() const { return (const_iterator(this->_dummyEnd)); }

			reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(this->end())); }

			reverse_iterator		rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(this->begin())); }

			self_type& operator=(const self_type& tree)
			{
				this->clear();
				this->_alloc = tree._alloc;
				this->_nodeAlloc = tree._nodeAlloc;
				this->_comp = tree._comp;

				this->_root = NULL;
				this->createEndNode();
	
				for (const_iterator it = tree.begin(); it != tree.end(); ++it)
					this->insert(*it);

				this->setEndNodeAtTheEnd();
				
				return (*this);
			}

			void swap(self_type& x)
			{
				node_pointer tmp_root = this->_root;
				node_pointer tmp_dummyEnd = this->_dummyEnd;
				node_allocator_type tmp_nodeAlloc = this->_nodeAlloc;
				allocator_type tmp_alloc = this->_alloc;
				data_compare tmp_comp = this->_comp;

				this->_root = x._root;
				this->_dummyEnd = x._dummyEnd;
				this->_nodeAlloc = x._nodeAlloc;
				this->_alloc = x._alloc;
				this->_comp = x._comp;

				x._root = tmp_root;
				x._dummyEnd = tmp_dummyEnd;
				x._nodeAlloc = tmp_nodeAlloc;
				x._alloc = tmp_alloc;
				x._comp = tmp_comp;
			}

			size_type max_size() const { return (this->_nodeAlloc.max_size()); }

	};

}

#endif