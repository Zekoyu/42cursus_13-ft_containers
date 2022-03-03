/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 03-03-2022 13:32 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include "iterator_traits.hpp"

namespace ft
{
	
	/*
		Iterator tags are used to determine of which type is a given operator.

		They are mostly used for optimization purposes, for instance if we have
		different implementations of a function depending on the iterator type, instead
		of checking for the type at runtype (if is_random_access_iterator(it))
		we can check it at compile time using iterator_traits<it>::iterator_category
	*/

	/* Defines an input iterator (Reads forward) */
	struct input_iterator_tag { };

	/* Defines an output iterator (Writes forward) */
	struct output_iterator_tag { };

	/* Defines a forward iterator (Reads/Writes forward) */	
	struct forward_iterator_tag : public input_iterator_tag { };

	/* Define a bidirectional iterator (Reads/Writes forward/backward) */
	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	/* Define a random access iterator (Read/Writes anywhere (random access like an array)) */
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Iterator>
	class reverse_iterator
	{
		private:
			iterator_type _it;
		public:
			typedef Iterator											iterator_type;
			typedef ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef ft::iterator_traits<Iterator>::value_type			value_type;
			typedef ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef ft::iterator_traits<Iterator>::pointer				pointer;
			typedef ft::iterator_traits<Iterator>::reference			reference;

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

			iterator_type	base() const { return (iterator_type); }

			/* Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it. */
			reference operator*() const
			{
				iterator_type temp = this->_it;
				--this->_it;
				return (*it);	
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


	/* Iterator class is a template used to simplify custom iterator creation by defining required types for iterators,
	   the custom iterator should just inherit from ft::iterator and provide at least Category and T. Then there is no need to redefine value_type etc.*/
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct Iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};
	
}