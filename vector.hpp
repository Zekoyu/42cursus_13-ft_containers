/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 14-03-2022 13:07 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterators.hpp"
#include "enable_if.hpp"
#include "comparisons.hpp"
#include "VectorIterator.hpp"

#include <memory>
#include <stdexcept>
#include <limits>

namespace ft
{	// > > instead of >> because otherwise C++ might think it's a bitshift
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* IMO typedefs first, then pivate members, then public */
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			/* All of these could be used with value_type for the default allocator, but maybe not custom ones */
			typedef typename allocator_type::reference			reference; /* Same as value_type& */
			typedef typename allocator_type::const_reference	const_reference; /* Same as const value_type& */
			typedef typename allocator_type::pointer			pointer; /* Same as value_type* */
			typedef typename allocator_type::const_pointer		const_pointer; /* Same as const value_type* */

			typedef VectIterator<T, false>	iterator;
			typedef VectIterator<T, true>	const_iterator;
			/* if we define a non-const vector and call vector::const_iterator it = begin(), compiler has no way to know we want const version
			   https://stackoverflow.com/questions/2844339/c-iterator-and-const-iterator-problem-for-own-container-class */
			typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			/* Identical to iterator_traits<iterator>::size_type/difference_type */
			typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t													size_type; /* Can hold any positive value of difference_type*/
		
		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			/* Like std::distance but worse.
			   Actual point is because the std version does not work with ft::<any_iterator>_tag */
			template <class InputIterator>
			typename ft::iterator_traits<InputIterator>::difference_type
			distance(InputIterator first, InputIterator last)
			{
				size_type i = 0;
				while (first++ != last)
					++i;
				return (i);
			}

			// Move elements distance away (to the right) starting at index (included), DOES NOT modify size
			// Vector = 1, 2, 3, 4, 5 moveElementsRight(2, 5) => 1, 2, -, -, -, -, -, 3, 4, 5 
			void moveElementsRight(size_type index, size_type distance)
			{
				if (this->_capacity == 0)
					this->reserve(1);

				// Since we don't know the final size, use while loop
				while (this->_size + distance > this->_capacity)
					this->reserve(this->_capacity * 2);

				// From end to start because otherwise we modify the next slot we are going to copy
				// Eg. copy 0 to 1, then copy 1 to 2 would cause 0 = 1 = 2
				// If distance is 0, we copy to the same slot then delete, to avoid that check first
				if (this->_size == 0 || distance == 0)
					return ;

				for (size_type i = this->_size - 1; i >= index; --i)
				{
					this->_alloc.construct(this->_ptr + i + distance, this->_ptr[i]); // Copy the value distance slots away
					this->_alloc.destroy(this->_ptr + i); // Destroy the original value
					// Repeat
					if (i == 0) // If i == 0 and index is 0, manually break otherwise i would overflow next iteration
						return ;
				}
			}

			// Move elements distance away (to the left) starting at index (excluded), DOES NOT modify size
			// Vector = 1, 2, 3, 4, 5 moveElementsLeft(0, 1) => 2, 3, 4, 5, -
			void moveElementsLeft(size_type index, size_type distance)
			{
				// From start because otherwise we modify the next slot we are going to copy
				// Eg. copy 2 to 1, then copy 1 to 0 would cause 2 = 1 = 0
				// If distance is 0, we copy to the same slot then delete, to avoid that check first
				if (this->_size == 0 || distance == 0)
					return ;

				for (size_type i = index; i + distance < this->_size; ++i)
				{
					this->_alloc.construct(this->_ptr + i, this->_ptr[i + distance]); // Copy the value from distance slots away
					this->_alloc.destroy(this->_ptr + i + distance); // Destroy the original value
					// Repeat
				}
			}


		public:
			/* Default constructor */
			vector(const allocator_type& alloc = allocator_type()) : _ptr(0), _size(0), _capacity(0), _alloc(alloc) { }

			/* Fill constructor */
			/* The compiler is allow to make one implicit conversion to resolve parameters to a function, here we don't allow it.
			   Eg. foo(Bar) with Bar(int) existing, we can call foo(42) with an int since compiler knows there is a Bar(int) it will do Bar(42) implicitely. */
			explicit vector(size_type n, const value_type& val = value_type(),
							 const allocator_type& alloc = allocator_type()) : _ptr(0), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(n, val);
			}

			/* Range constructor */
			template <class InputIterator>
        	vector(InputIterator first, InputIterator last,
				   const allocator_type& alloc = allocator_type()) : _ptr(0), _size(0), _capacity(0), _alloc(alloc)
			{
				this->assign(first, last);
			}

			/* Copy constructor */
			vector(const vector& x) : _ptr(0), _size(0), _capacity(0), _alloc(x.get_allocator())
			{
				this->resize(x._size); /* First resize to initialize capacity and size */				
				
				for (size_type i = 0; i < x._size; ++i)
					this->_alloc.construct(this->_ptr + i, x._ptr[i]);
				this->_size = x._size;
			}

			~vector()
			{
				this->clear();
				this->_alloc.deallocate(this->_ptr, this->_capacity);
			}

			iterator		begin() { return (iterator(this->_ptr)); }
			const_iterator	begin() const { return (const_iterator(this->_ptr)); }

			iterator		end() { return (iterator(this->_ptr + _size)); }
			const_iterator	end() const { return (const_iterator(this->_ptr + _size)); }

			reverse_iterator		rbegin() { return (reverse_iterator(this->end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(this->end())); }

			reverse_iterator		rend() { return (reverse_iterator(this->begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(this->begin())); }

			// reverse_iterator		rbegin() { return (ft::reverse_iterator<iterator>(this->end())); } /* Returns reverse iterator starting from vector.end() */
			// const_reverse_iterator	rbegin() const { return (ft::reverse_iterator<const_iterator>(this->end())); } /* Same but const */

			// reverse_iterator		rend() { return (ft::reverse_iterator<iterator>(this->begin())); } /* Same but starting at vector.begin() */
			// const_reverse_iterator	rend() const { return (ft::reverse_iterator<const_iterator>(this->begin())); }  /* Again same but const */
	
			size_type	size() const { return (this->_size); }
			/* This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max()
			   At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
			   Can also use Allocator.max_size since vector is contiguous memory */
			size_type	max_size() const { return (this->_alloc.max_size()); }

			/* Truncate if n < size; append otherwise, if n > capacity, realloc */
			void resize(size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("resize: value requested too big"));
				if (n > this->_size)
				{
					if (n > this->_capacity) /* Realloc of size n */
					{
						pointer tmp = this->_alloc.allocate(n);
						for (size_type i = 0; i < this->_size; ++i) /* Move content */
							this->_alloc.construct(tmp + i, this->_ptr[i]);
						for (size_type i = this->_size; i < n; ++i) /* Append new content */
							this->_alloc.construct(tmp + i, val);
						this->_alloc.deallocate(this->_ptr, this->_capacity);
						this->_ptr = tmp;
						this->_capacity = n;
						this->_size = n;
					}
					else /* Append without realloc */
					{
						for (size_type i = this->_size; i < n; ++i)
							this->_alloc.construct(this->_ptr + i, val);
					}
				}
				else
				{
					this->_size = n;
					/* If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them). */
					for (size_type i = n; i < this->_capacity; ++i)
						this->_alloc.destroy(this->_ptr + i);
				}
				this->_size = n;
			}

			size_type capacity() const { return (this->_capacity); }

			bool	empty() const { return (this->_size == 0); }

			void	reserve(size_type n)
			{
				if (n <= this->_capacity)
					return;
				
				pointer tmp = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; ++i) /* Move content */
				 	this->_alloc.construct(tmp + i, this->_ptr[i]);
				this->_alloc.deallocate(this->_ptr, this->_capacity);
				this->_ptr = tmp;
				this->_capacity = n;
			}

			reference		operator[](size_type n) { return (*(this->_ptr + n)); }
			const_reference	operator[](size_type n) const { return (*(this->_ptr + n)); }

			vector&	operator=(const vector& x)
			{
				/* If x capacity is 150 but size is 7, at least on linux, new capacity will be 7 */
				this->resize(x._size); /* If this.capacity is bigger than x, do not downgrade */
				this->clear();
				
				for (size_type i = 0; i < x._size; ++i)
					this->_alloc.construct(this->_ptr + i, x._ptr[i]);
				this->_size = x._size;
				return (*this); /* Forget the return, get and "illegal hardware exception" :) */
			}

			reference		at(size_type n)
			{
				if (n >= this->_size)
					throw (std::out_of_range("index is out of range"));
				return ((*this)[n]); /* this->operator[](n) */
			}

			const_reference	at(size_type n) const
			{
				if (n >= this->_size)
					throw (std::out_of_range("index is out of range"));
				return (this->operator[](n)); /* same as (*this)[n] */
			}

		    reference		front() { return (*this->_ptr); }
			const_reference	front() const { return (*this->_ptr); }

			reference		back() { return (*(this->_ptr + this->_size - 1)); }
			const_reference	back() const { return (*(this->_ptr + this->_size - 1)); }

			void	assign(size_type n, const value_type& val)
			{
				this->reserve(n);
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_ptr + i);
				for (size_type i = 0; i < n; ++i)
					this->_alloc.construct(this->_ptr + i, val);
				this->_size = n;
			}

			/* The range used is [first,last), which includes all the elements between first and last, 
			   including the element pointed by first but not the element pointed by last  */
			template <class InputIterator>
			void	assign(InputIterator first, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer ,InputIterator>::type last)
			{
				this->reserve(this->distance(first, last));
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_ptr + i);
				
				this->_size = this->distance(first, last); // Set distance first since we modify first after

				for (size_type i = 0; first != last; ++first, ++i)
					this->_alloc.construct(this->_ptr + i, *first);
			}

			/* If the array is not enough to hold value, double it's size */
			void	push_back(const value_type& val)
			{
				if (this->_capacity == 0)
					this->reserve(1);
				else if (this->_size + 1 > this->_capacity)
					this->reserve(this->_capacity * 2);

				this->_alloc.construct(this->_ptr + this->_size, val); /* this->_size = one after last element */
				++this->_size;
			}

			void	pop_back()
			{
				this->_alloc.destroy(this->_ptr + this->_size - 1);
				--this->_size;
			}

			/* Returns an iterator pointing to first new elt to check iterator invalidion (partial or total), if return value == position, everything before position is still valid,
			   otherwise not, if it's != all iterators are invalidated */
			iterator insert(iterator position, const value_type& val)
			{
				size_type index = this->distance(this->begin(), position);

				// Move everything one slot to the right, starting at index
				this->moveElementsRight(index, 1);

				// Set the one value at index
				this->_alloc.construct(this->_ptr + index, val);
				++this->_size;
				return (iterator(this->_ptr + index));
			}

			void insert(iterator position, size_type n, const value_type& val)
			{
				size_type index = this->distance(this->begin(), position);

				// Same as above, except we move n instead of 1
				this->moveElementsRight(index, n);

				// Fill the "blank" slots
				for (size_type i = 0; i < n; ++i)
				{
					this->_alloc.construct(this->_ptr + index + i, val);
					++this->_size;
				}
			}

			// Same as above, except now N is the distance between first and last
			/* enable_if to avoid size_type as InputIterator, with an int vector we
			   want the above version of insert to be called, but this one matches too.
			   We basically need an enable_if always true for any InputIterator, but not for size_type / difference_type,
			   which makes is_integer (which fortunately is C++98) a perfect choice */
			template<class InputIterator>
			void insert(iterator position, InputIterator first, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer ,InputIterator>::type last)
			{
				size_type index = this->distance(this->begin(), position);
				size_type n = 0;

				InputIterator firstCpy(first);
				while (firstCpy++ != last)
					++n;

				this->moveElementsRight(index, n);

				// Fill the "blank" slots
				for(size_type i = 0; first != last; ++i)
				{
					this->_alloc.construct(this->_ptr + index + i, *first);
					++first;
					++this->_size;
				}
			}

			iterator erase(iterator position)
			{
				if (this->_size == 0)
					return (this->end());
					
				size_type index = this->distance(this->begin(), position);

				// Destroy the given element
				this->_alloc.destroy(this->_ptr + index);

				// Shift everything left
				this->moveElementsLeft(index, 1);
				
				--this->_size;
				return (iterator(this->_ptr + index)); // Since we removed element at index, returning ptr + index returns the one following the deleted element
			}

			// If first == last, then remove basically nothing
			// 1
			iterator erase(iterator first, iterator last)
			{
				size_type index = this->distance(this->begin(), first);
				size_type n = this->distance(first, last);

				if (index >= this->_size) // past the end or equal
					return (this->end());

				/* Since we include first but not last, use strict <, only special case is when first == last
				   because first should be included but not last, but it is handled right above in case n == 0 */
				// As above, destroy the elements, but every one in range [first-last) instead of 1
				for (size_type i = index; i < index + n; ++i)
					this->_alloc.destroy(this->_ptr + i);

				// Shift everything left
				this->moveElementsLeft(index, n);

				this->_size -= n;
				return (iterator(this->_ptr + index)); /* Since we removed element at index, returning ptr + index returns the one following the deleted element */
			}

			void swap(vector& x)
			{
				pointer		tmp_ptr = this->_ptr;
				size_type	tmp_size = this->_size;
				size_type	tmp_capacity = this->_capacity;

				this->_ptr = x._ptr;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._ptr = tmp_ptr;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			/* deallocate does not destroy elements, see std::allocator::deallocate cplusplus.com */
			void clear()
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_ptr + i);
				this->_size = 0;
			}

			allocator_type get_allocator() const
			{
				return (allocator_type());
			}
	};

	/* Should be optimized, but who cares */
	template <class T, class Alloc>
	void swap(ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	/* We are not forced to write template arguments since compiler template
	   deduction does it automatically */
	template <class T, class Alloc>
	bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs)); /* Either <= or > */
	}

	template <class T, class Alloc>
	bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs)); /* Either < or >= */
	}

}

#endif