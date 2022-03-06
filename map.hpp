/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 06-03-2022  by  `-'                        `-'                  */
/*   Updated: 06-03-2022 21:40 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include "pairs.hpp"
#include "iterators.hpp"

#include <memory>
#include <functional>

namespace ft
{

	template < class Key,                                     			// map::key_type
			   class T,                                       			// map::mapped_type
			   class Compare = std::less<Key>,                   		// map::key_compare
			   class Alloc = std::allocator<ft::pair<const Key,T> >	>	// map::allocator_type
	class map
	{
		public:
			template <class Map>
			class MapIterator;

			typedef Key								key_type;
			typedef T								mapped_type;
			typedef pair<key_type, mapped_type>		value_type;
			typedef Compare							key_compare;
			typedef value_comp						value_compare;
			typedef Alloc							allocator_type;

			typedef allocator_type::reference		reference;
			typedef allocator_type::const_reference	const_reference;
			typedef allocator_type::pointer			pointer;
			typedef allocator_type::const_pointer	const_pointer;
		
			/* When dereferencing iterator we access a std::pair<Key, T>, just like vector access T */
			typedef MapIterator< map<Key, T, Compare, Alloc> >				iterator;
			typedef MapIterator< map<const Key, const T, Compare, Alloc> >	const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			/* Identical to iterator_traits<iterator>::size_type/difference_type */
			typedef ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef ft::iterator_traits<iterator>::size_type		size_type;
	
		private:
			/* Binary tree = well, binary tree */
			/* Binary search tree is more organized:
				- Left subtree contains only nodes with key lesser than the current one
				- Opposite for right subtree
				- Each subtree must be a binary search tree
				- No duplicate nodes
			*/
			struct Node
			{

			};

			Node*	_root;

	};

}

#endif