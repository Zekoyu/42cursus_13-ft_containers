/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 02-03-2022  by  `-'                        `-'                  */
/*   Updated: 02-03-2022 14:14 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

	template <class Iterator>
	class reverse_iterator
	{
		private:
			Iterator _it; /* Cannot use iterator_type since it's declared after */
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			/* Default constructor */
			reverse_iterator() : _it() { };

			/* Initialization constructor */
			/* For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1) is always true (as long as r is dereferenceable);
			   thus a reverse iterator constructed from a one-past-the-end iterator dereferences to the last element in a sequence,
			   and a reverse iterator constructed from the begin iterator point to the element before it (which is the past-the-end element in the reversed range) */
			explicit reverse_iterator (iterator_type it) : _it(it) { }

			/* Copy constructor, takes another reverse_iterator of the same type as argument, preserve the sense of iteration */
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) { }

			/* Since reverse_iterators basically have an offset of -1 compared to the original iterator, if we call base on ft::vector<int>::rbegin(), it would point to ft::vector<int>::end(), and call on rend() would point to begin() */
			iterator_type	base() const { return(this->_it); }

			/* Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it. */
			reference operator*() const
			{
				iterator_type temp = this->_it;
				--this->_it;
				return (temp);	
			}

			/* Internally, the function applies the binary operator- on the base iterator and returns a reverse iterator constructed with the resulting iterator value. */
			reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(this->_it - n)); }

			/* Internally, the pre-increment version (1) decrements the base iterator kept by the object (as if applying operator-- to it). */
			reverse_iterator& operator++()
			{
				--this->_it;
				return (*this);
			}

			/* The post-increment version (2) is implemented with a behavior equivalent to: */
			reverse_iterator  operator++(int)
			{
				reverse_iterator temp = *this;
				++(*this);
				return (temp);
			}

			/* Internally, the function decreases by n the base iterator kept by the object (as if applying operator-= to it). */
			reverse_iterator& operator+= (difference_type n)
			{
				this->_it -= n;
				return (*this);
			}

			/* Decrement operators are the same as increment reversed */
			reverse_iterator operator- (difference_type n) const { return (reverse_iterator(this->_it + n)); }

			reverse_iterator& operator--()
			{
				++this->_it;
				return (*this);
			}

			reverse_iterator  operator--(int)
			{
				reverse_iterator temp = *this;
				--(*this);
				return (temp);
			}

			reverse_iterator& operator-= (difference_type n)
			{
				this->_it += n;
				return (*this);
			}

			/* Internally, the function calls operator* and returns its address, as if implemented as: */
			pointer operator->() const { return &(operator*()); }

			/* Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1]. */
			reference operator[] (difference_type n) const { return (this->base()[-n-1]); }
	};

}
#endif
