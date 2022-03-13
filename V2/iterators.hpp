/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 13-03-2022 19:18 by                                             */
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

	// template <class Iterator>
	// class reverse_iterator
	// {
	// 	public:
	// 		typedef Iterator													iterator_type;
	// 		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	// 		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	// 		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	// 		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	// 		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	// 	private:
	// 		iterator_type _it;

	// 	public:
	// 		/* Default constructor */
	// 		reverse_iterator() : _it() { };

	// 		/* Initialization constructor */
	// 		/* For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1) is always true (as long as r is dereferenceable);
	// 		   thus a reverse iterator constructed from a one-past-the-end iterator dereferences to the last element in a sequence,
	// 		   and a reverse iterator constructed from the begin iterator point to the element before it (which is the past-the-end element in the reversed range) */
	// 		explicit reverse_iterator(iterator_type it) : _it(it) { }

	// 		/* Copy constructor, takes another reverse_iterator of the same type as argument, preserve the sense of iteration */
	// 		template <class Iter>
	// 		reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) { }

	// 		iterator_type	base() const { return (this->_it); }

	// 		/* Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it. */
	// 		reference operator*() const
	// 		{
	// 			iterator_type tmp = this->_it;
	// 			--tmp;
	// 			return (*tmp);	
	// 		}

	// 		/* Internally, the function applies the binary operator- on the base iterator and returns a reverse iterator constructed with the resulting iterator value. */
	// 		reverse_iterator operator+(difference_type n) const { return (reverse_iterator(this->_it - n)); }

	// 		/* For the tester, 1 + it ... */
	// 		friend reverse_iterator operator+(difference_type n, const reverse_iterator& rhs)
	// 		{
	// 			return (rhs + n);
	// 		}
					
	// 		/* Internally, the pre-increment version (1) decrements the base iterator kept by the object (as if applying operator-- to it). */
	// 		reverse_iterator& operator++()
	// 		{
	// 			--this->_it;
	// 			return (*this);
	// 		}

	// 		/* The post-increment version (2) is implemented with a behavior equivalent to: */
	// 		reverse_iterator  operator++(int)
	// 		{
	// 			reverse_iterator temp = *this;
	// 			++(*this);
	// 			return (temp);
	// 		}

	// 		/* Internally, the function decreases by n the base iterator kept by the object (as if applying operator-= to it). */
	// 		reverse_iterator& operator+=(difference_type n)
	// 		{
	// 			this->_it -= n;
	// 			return (*this);
	// 		}

	// 		/* Decrement operators are the same as increment reversed */
	// 		// difference_type operator-(const reverse_iterator& rit) const { return (rit._it - this->_it); };

	// 		// reverse_iterator operator-(difference_type n) const { return (reverse_iterator(this->_it.operator+(n))); };


	// 		/* Internally, the function applies the binary operator- on the base iterator and returns a reverse iterator constructed with the resulting iterator value. */
	// 		reverse_iterator operator-(difference_type n) const { return (reverse_iterator(this->_it + n)); }

	// 		difference_type operator-(const reverse_iterator& rit) const { return (this->base() + rit.base()); }

	// 		reverse_iterator& operator--()
	// 		{
	// 			++this->_it;
	// 			return (*this);
	// 		}

	// 		reverse_iterator  operator--(int)
	// 		{
	// 			reverse_iterator tmp = *this;
	// 			--(*this);
	// 			return (tmp);
	// 		}

	// 		reverse_iterator& operator-=(difference_type n)
	// 		{
	// 			this->_it += n;
	// 			return (*this);
	// 		}

	// 		/* Internally, the function calls operator* and returns its address, as if implemented as: */
	// 		pointer operator->() const { return &(operator*()); }

	// 		/* Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1]. */
	// 		reference operator[](difference_type n) const { return (this->base()[-n-1]); }

	// 		friend bool operator==(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);
	// 		friend bool operator!=(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);
	// 		friend bool operator<(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);
	// 		friend bool operator<=(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);
	// 		friend bool operator>(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);
	// 		friend bool operator>=(const ft::reverse_iterator<iterator_type>& lhs, const ft::reverse_iterator<iterator_type>& rhs);

	// 		template <class Iter>
	// 		reverse_iterator& operator=(const reverse_iterator<Iter>& rit);
	// };
	
	// template <class Iter> template <class U>
	// reverse_iterator<Iter>& reverse_iterator<Iter>::operator=(const reverse_iterator<U>& u) {
	// 	this->_it = u.base();
	// 	return (*this);
	// };

	// template< class Iterator1, class Iterator2 >
	// bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() == rhs.base()); }

	// template< class Iterator1, class Iterator2 >
	// bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() != rhs.base()); }

	// template< class Iterator1, class Iterator2 >
	// bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() < rhs.base()); }

	// template< class Iterator1, class Iterator2 >
	// bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() <= rhs.base()); }

	// template< class Iterator1, class Iterator2 >
	// bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() > rhs.base()); }

	// template< class Iterator1, class Iterator2 >
	// bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
	// { return (lhs.base() >= rhs.base()); }

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