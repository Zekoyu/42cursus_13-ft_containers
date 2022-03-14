/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 13:11 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

#include <cstddef>

namespace ft
{
	/*******************************************************
	 *                    Iterator tags                    *
	 *******************************************************/

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
	


	/*******************************************************
	 *                   Iterator traits                   *
	 *******************************************************/

	/* Iterator traits of another iterator are value taken from it */
	template <class Iterator>
	struct iterator_traits /* struct so that it's public by default */
	{
		typedef typename Iterator::difference_type		difference_type; /* Difference between 2 iterators (used by std::distance, typically int for iterators, ptrdiff_t for pointers) */
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	/* Iterator traits of a pointer are just the value pointer to by this pointer (for classes with no iterators but just raw pointer) */
	template <class T>
	struct iterator_traits<T*> /* Specialization of iterator_traits with any pointer type (same as iterator_traits<char> for specializing char for instance) */
	{
		typedef ptrdiff_t	difference_type; /* Literally the distance type (result of substraction) between 2 pointer */
		typedef T			value_type;
		typedef T*			pointer;
		typedef T&			reference;
		typedef ft::random_access_iterator_tag	iterator_category; /* Since it's a pointer, it should be pointing to contiguous memory, so can be accessed at random */
	};

	/* Same specialization for pointers to const */
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t	difference_type;
		typedef T			value_type;
		typedef T*			pointer;
		typedef T&			reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};


	/*******************************************************
	 *                  Reverse iterator                   *
	 *******************************************************/

	/*
		Iterator tags are used to determine of which type is a given operator.

		They are mostly used for optimization purposes, for instance if we have
		different implementations of a function depending on the iterator type, instead
		of checking for the type at runtype (if is_random_access_iterator(it))
		we can check it at compile time using iterator_traits<it>::iterator_category
	*/

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		private:
			iterator_type _it;

		public:
			/********** Constructors **********/
			reverse_iterator() : _it() { }

			/* For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1) is always true (as long as r is dereferenceable);
			   thus a reverse iterator constructed from a one-past-the-end iterator dereferences to the last element in a sequence,
			   and a reverse iterator constructed from the begin iterator point to the element before it (which is the past-the-end element in the reversed range) */
			explicit reverse_iterator(iterator_type it) : _it(it) { }

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) { }

			/********** Member functions **********/
			// _it will be copied since we don't return by reference
			iterator_type base() const { return (_it); }

			// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
			reference operator*() const { iterator_type tmp = this->_it; --tmp; return (*tmp); }


			reverse_iterator operator+(difference_type n) const { return (reverse_iterator(this->_it.operator-(n))); }

			reverse_iterator& operator++() { --this->_it; return (*this); }

			reverse_iterator operator++(int) { reverse_iterator tmp = *this; ++(*this); return (tmp); }

			reverse_iterator& operator+=(difference_type n) { this->_it -= n; return (*this); }


			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(this->_it.operator+(n))); }

			reverse_iterator& operator--() { ++this->_it; return (*this); }

			reverse_iterator operator--(int) { reverse_iterator tmp = *this; --(*this); return (tmp); }

			reverse_iterator& operator-=(difference_type n) { this->_it += n; return (*this); }

			// Internally, the function calls operator* and returns its address, as if implemented as:
			pointer operator->() const { return (&(this->operator*())); }

			// Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
			reference operator[](difference_type n) const { return (this->base()[-n-1]); }
	};

	// Relational operators, see https://www.cplusplus.com/reference/iterator/reverse_iterator/operators/
	template<class IteLeft, class IteRight>
	bool operator==(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() == rhs.base()); }

	template<class IteLeft, class IteRight>
	bool operator!=(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() != rhs.base()); }

	template<class IteLeft, class IteRight>
	bool operator<(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() > rhs.base()); }

	template<class IteLeft, class IteRight>
	bool operator<=(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() >= rhs.base()); }

	template<class IteLeft, class IteRight>
	bool operator>(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() < rhs.base()); }

	template<class IteLeft, class IteRight>
	bool operator>=(const ft::reverse_iterator<IteLeft>& lhs, const ft::reverse_iterator<IteRight>& rhs)
	{ return (lhs.base() <= rhs.base()); }


	// Operator+ returns a reverse_iterator
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{ return (rev_it + n); }

	// Whereas operator- return only difference_type, again, see cplusplus.com
	// The function returns the same as subtracting lhs's base iterator from rhs's base iterator.
	template<class Iterator>
 	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ return (rhs.base() - lhs.base()); }

	// To allow const_reverse_iterator - const_iterator and reverse way
	// Not written on cplusplus.com but implemented in every STL iterator
	template<class IteLeft, class IteRight>
 	typename reverse_iterator<IteRight>::difference_type operator-(const reverse_iterator<IteLeft>& lhs, const reverse_iterator<IteRight>& rhs)
	{ return (rhs.base() - lhs.base()); }

	/*******************************************************
	 *              Iterator template / base               *
	 *******************************************************/

	/* Iterator class is a template used to simplify custom iterator creation by defining required types for iterators,
	   the custom iterator should just inherit from ft::iterator and provide at least Category and T. Then there is no need to redefine value_type etc.*/
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

}
#endif