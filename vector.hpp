/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 04-03-2022 17:25 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include "iterators.hpp"

namespace ft
{
	/* InIterator, OutIterator, ForIterator, BiIterator, RandIterator
		These are generic type names used for (respectively) input iterators, output iterators, forward iterators, bidirectional iterators, and random access iterators.
		For example, vector<int>::iterator is a RandIterator, while list<string>::iterator is a BiIterator. */
	template <typename Vector>
	class RandIterator : public ft::iterator<ft::random_access_iterator_tag, Vector::value_type> /* Only define 2 types since the 3 other default values are those we want */
	{
		public:
			typedef Vector::value_type		value_type;
			typedef Vector::reference		reference;
			typedef Vector::pointer			pointer;
			typedef Vector::difference_type	difference_type;
			
			RandIterator(pointer ptr) : _ptr(ptr) { }

			RandIterator&	operator++() /* prefix */
			{
				++this->_ptr;
				return (*this);
			}

			RandIterator&	operator++(int) /* postfix */
			{
				RandIterator tmp = *this;
				++(*this); /* so that if we want to change code, only change the prefix one */
				return (tmp);
			}

			RandIterator&	operator--() /* prefix */
			{
				--this->_ptr;
				return (*this);
			}

			RandIterator&	operator--(int) /* postfix */
			{
				RandIterator tmp = *this;
				--(*this);
				return (tmp);
			}

			/* Returns a reference to the type held, same as T& */
			reference	operator[](size_type index)
			{
				return (*(this->_ptr[index]));
			}

			/* Calling Foo->x becomes the same as Foo.operator->()->x  or *(Foo.operator->()x)
				The compiler calls the operator -> as many times as needed to get a raw pointer, then dereferences it */
			pointer	operator->()
			{
				return (this->_ptr);
			}

			reference	operator*()
			{
				return (*this->_ptr); /* operator* has lower precedence than ->/. and associativity is from right to left, so no need for parentheses even if we used *this->value.someOtherValue->data */
			}

			bool	operator==(const RandIterator& r)
			{
				return (this->_ptr == r._ptr);
			}

			bool	operator!=(const RandIterator& r)
			{
				return (!(*this == r));
			}

			RandIterator&	operator+(difference_type n)
			{
				RandIterator tmp = *this;
				this->_ptr += n;
				return (tmp);
			}

			RandIterator&	operator+(const RandIterator& r)
			{
				RandIterator tmp = *this;
				this->_ptr += r._ptr;
				return (tmp);
			}

			RandIterator&	operator+=(difference_type n)
			{
				this->_ptr += n;
				return (*this);
			}

			RandIterator&	operator-(difference_type n)
			{
				RandIterator tmp = *this;
				this->_ptr -= n;
				return (tmp);
			}

			RandIterator&	operator-(const RandIterator& r)
			{
				RandIterator tmp = *this;
				this->_ptr -= r._ptr;
				return (tmp);
			}

			RandIterator&	operator-=(difference_type n)
			{
				this->_ptr -= n;
				return (*this);
			}				

		private:
			pointer	_ptr;
	};

	// > > instead of >> because otherwise C++ might think it's a bitshift
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* IMO typedefs first, then pivate members, then public */
		public:
			public:
			typedef T								value_type;
			typedef Allocator						allocator_type;
			/* All of these could be used with value_type for the default allocator, but maybe not custom ones */
			typedef allocator_type::reference		reference; /* Same as value_type& */
			typedef allocator_type::const_reference	const_reference; /* Same as const value_type& */
			typedef allocator_type::pointer			pointer; /* Same as value_type* */
			typedef allocator_type::const_pointer	const_pointer; /* Same as const value_type* */

			typedef RandIterator< vector<T, Allocator> >		iterator;
			typedef RandIterator< vector<const T, Allocator> >	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef size_t							size_type; /* Enough to hold any positive integral type (integer) */
			typedef ptrdiff_t						difference_type;
		
		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;


		public:
			vector() : _ptr(0), _size(0), _capacity(0) { }

			iterator		begin() { return (RandIterator(_ptr)); }
			const_iterator	begin() const { return (RandIterator(_ptr)); }

			iterator		end() { return (RandIterator(_ptr + _size)); }
			const_iterator	end() const { return (RandIterator(_ptr + _size)); }

			reverse_iterator		rbegin() { return (ft::reverse_iterator<iterator>(this->end())); } /* Returns reverse iterator starting from vector.end() */
			const_reverse_iterator	rbegin() const { return (ft::reverse_iterator<const_iterator>(this->end())); } /* Same but const */

			reverse_iterator		rend() { return (ft::reverse_iterator<iterator>(this->begin())); } /* Same but starting at vector.begin() */
			const_reverse_iterator	rend() const { return (ft::reverse_iterator<const_iterator>(this->begin())); }  /* Again same but const */
	
			size_type	size() const { return (this->_size); }
			/* This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max()
			   At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
			   Can also use Allocator.max_size since vector is contiguous memory */
			size_type	max_size() const { return (_alloc.max_size()); }

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
							this->_alloc.construct(tmp + i, this->_ptr + i);
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
							this->_ptr + i = val;
					}
				}
				else
				{
					this->_size = n;
					/* If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them). */
					for (size_type i = n; i < this->capacity; ++i)
						this->_alloc.destroy(this->_ptr + i);
				}
				this->_size = n;
			}

			size_type capacity() const { return (this->_capacity); }

			bool	empty() const { return (this->_size == 0); }

			void	reserve(size_type n)
			{
				if (n > this->_capacity)
				{
					pointer tmp = this->_alloc.allocate(n);
					for (size_type i = 0; i < this->_size; ++i) /* Move content */
						this->_alloc.construct(tmp + i, this->_ptr + i);
					for (size_type i = this->_size; i < n; ++i) /* Append new content */
						this->_alloc.construct(tmp + i, val);
					this->_alloc.deallocate(this->_ptr, this->_capacity);
					this->_ptr = tmp;
					this->_capacity = n;
				}
			}

			reference		operator[] (size_type n) { return (this->_ptr + n); }
			const_reference	operator[] (size_type n) const { return (this->_ptr + n); }

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

			reference		back() { return (this->_ptr + this->_size - 1); }
			const_reference	back() const { return (this->_ptr + this->_size - 1); }

			void	assign(size_type n, const value_type& val)
			{
				this->reserve(n);
				for (size_type i = 0; i < n; ++i)
				{
					this->_alloc.destroy(this->_ptr + i);
					this->_alloc.construct(this->_ptr + i, val)
				}
			}

			/* The range used is [first,last), which includes all the elements between first and last, 
			   including the element pointed by first but not the element pointed by last */
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				this->reserve(std::distance(first, last) - 1); /* size needed */
				size_type i = 0;
				while (first != last)
				{
					this->_alloc.destroy(this->_ptr + i);
					this->_alloc.construct(this->_ptr + i, *first);
					++first;
				}
			}

			/* If the array is not enough to hold value, double it's size */
			void	push_back(const value_type& val)
			{
				if (this->_size + 1 > this->_capacity)
					this->reserve(this->capacity * 2);
				this->_alloc.construct(this->_ptr + this->size - 1, val);
				++this->size;
			}

			void	pop_back()
			{
				this->_alloc.destroy(this->_ptr + this->size - 1);
				--this->_size;
			}

			/* Returns an iterator pointing to first new elt to check iterator invalidion (partial or total), if return value == position, everything before position is still valid,
			   otherwise not, if it's != all iterators are invalidated */
			iterator	insert(iterator position, const value_type& val)
			{
				size_type index = std::distance(this->begin(), position);

				if (this->_size + 1 > this->_capacity)
					this->reserve(this->_capacity * 2);
				
				for (size_type i = this->_size - 1; i >= index; --i) /* Move everything and destroy the value at index */
				{
					this->_alloc.construct(this->_ptr + i + 1, this->_ptr + i);
					this->_alloc.destroy(this->_ptr + i);
				}
				this->_alloc.construct(this->_ptr + index), val);
				++this->_size;
				return (RandIterator(this->_ptr + index));
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				size_type index = std::distance(this->begin(), position);

				while (this->_size + n > this->_capacity) /* while instead of if in case we want to add many many values */
					this->reserve(this->_capacity * 2);
				for (size_type i = this->_size - 1; i >= (index + n); --i) /* Move everything and destroy the value at index */
				{
					this->_alloc.construct(this->_ptr + i + n, this->_ptr + i); /* Same as above except instead of moving 1 we move n to the right */
					this->_alloc.destroy(this->_ptr + i);
				}
				while (n--) /* Add n times */
				{
					this->_alloc.construct(this->_ptr + index++), val);
					++this->_size;
				}
			}

			/* Same as above using range instead of fixed value / size */
			template <class InputIterator>
  			void insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type n = std::distance(first, last);
				size_type index = std::distance(this->begin(), position);
				
				while (this->_size + n > this->_capacity)
					this->reserve(this->_capacity * 2);
				for (size_type i = this->_size - 1; i >= (index + n); --i)
				{
					this->_alloc.construct(this->_ptr + i + n, this->_ptr + i);
					this->_alloc.destroy(this->_ptr + i);
				}
				while (first != last)
				{
					this->_alloc.construct(this->_ptr + index++), *first);
					++first;
				}
			}

	};
	
}
