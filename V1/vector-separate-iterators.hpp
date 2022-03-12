/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 09-03-2022 17:48 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "iterators.hpp"
#include "enable_if.hpp"
#include "comparisons.hpp"

#include <memory>
#include <stdexcept>

/* The same version with separated const and non-const iterator */
namespace ft
{
	
	// > > instead of >> because otherwise C++ might think it's a bitshift
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* IMO typedefs first, then pivate members, then public */
		public:
			class iterator;
			class const_iterator;
			
			typedef T											value_type;
			typedef Allocator									allocator_type;
			/* All of these could be used with value_type for the default allocator, but maybe not custom ones */
			typedef typename allocator_type::reference			reference; /* Same as value_type& */
			typedef typename allocator_type::const_reference	const_reference; /* Same as const value_type& */
			typedef typename allocator_type::pointer			pointer; /* Same as value_type* */
			typedef typename allocator_type::const_pointer		const_pointer; /* Same as const value_type* */

			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef size_t		size_type; /* Enough to hold any positive integral type (integer) */
			typedef ptrdiff_t	difference_type;
		
		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			/* Like std::distance but worse.
			   Actual point is because the std version does not work with ft::<any_iterator>_tag */
			template <typename InputIterator>
			typename ft::iterator_traits<InputIterator>::difference_type
			distance(InputIterator first, InputIterator last)
			{
				size_type i = 0;
				while (first++ != last)
					++i;
				return (i);
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
			   including the element pointed by first but not the element pointed by last 
			   
			   Thanks to SNIFAE
			   3rd useless argument here just to check if InputIterator is really an iterator,
			   could also use enable_if but didn't found a suitable condition, std::is_integral
			   would not work with a vector of classes for instance */
			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last,
						   typename InputIterator::value_type* pouet = NULL)
			{
				(void) pouet;
				
				this->reserve(this->distance(first, last));
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(this->_ptr + i);
				this->_size = this->distance(first, last); /* Not at the end since we modify first */
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
			iterator	insert(iterator position, const value_type& val)
			{
				size_type index = this->distance(this->begin(), position);

				if (this->_capacity == 0)
					this->reserve(1);
				else if (this->_size + 1 > this->_capacity)
					this->reserve(this->_capacity * 2);
				
				for (size_type i = this->_size - 1; i >= index; --i) /* Move everything and destroy the value at index */
				{
					this->_alloc.construct(this->_ptr + i + 1, this->_ptr[i]);
					this->_alloc.destroy(this->_ptr + i);
					if (i == 0) /* Because --i would overflow since it's size_t */
						break; 
				}
				this->_alloc.construct(this->_ptr + index, val);
				++this->_size;
				return (iterator(this->_ptr + index));
			}

			void	insert(iterator position, size_type n, const value_type& val)
			{
				size_type index = this->distance(this->begin(), position);

				if (this->_capacity == 0)
					this->reserve(1);
				while (this->_size + n > this->_capacity) /* while instead of if in case we want to add many many values */
					this->reserve(this->_capacity * 2);

				for (size_type i = this->_size - 1; i >= (index + n); --i) /* Move everything and destroy the value at index */
				{
					this->_alloc.construct(this->_ptr + i + n, this->_ptr[i]); /* Same as above except instead of moving 1 we move n to the right */
					this->_alloc.destroy(this->_ptr + i);
					if (i == 0)
						break;
				}
				while (n--) /* Add n times */
				{
					this->_alloc.construct(this->_ptr + index, val);
					++this->_size;
					++index;
				}
			}

			/* Same as above using range instead of fixed value / size */
			template <typename InputIterator>
  			void insert(iterator position, InputIterator first, InputIterator last,
			  			typename InputIterator::value_type* pouet = NULL)
			{
				(void) pouet;
				
				size_type n = this->distance(first, last);
				size_type index = this->distance(this->begin(), position);

				if (this->_capacity == 0)
					this->reserve(1);
				while (this->_size + n > this->_capacity)
					this->reserve(this->_capacity * 2);
					
				/* Move everything, leave n unconstructed values */
				for (size_type i = this->_size - 1; i >= index; --i)
				{
					this->_alloc.construct(this->_ptr + i + n, this->_ptr[i]);
					this->_alloc.destroy(this->_ptr + i);
					if (i == 0)
						break;
				}
				/* Filling the "blank" spaces creating right above */
				while (first != last)
				{
					this->_alloc.construct(this->_ptr + index, *first);
					++first;
					++index;
					++this->_size;
				}
			}

			iterator erase(iterator position)
			{
				size_type index = this->distance(this->begin(), position);
				
				for (size_type i = index; i < this->_size - 1; ++i) /* Move everything to the left by 1 from index */
				{
					this->_alloc.destroy(this->_ptr + i);
					this->_alloc.construct(this->_ptr + i, this->_ptr[i + 1]);
				}
				this->_alloc.destroy(this->_ptr + this->_size - 1); /* Since we shifted everything to the left, destroy last element */
				--this->_size;
				return (iterator(this->_ptr + index)); /* Since we removed element at index, returning ptr + index returns the one following the deleted element */
			}

			iterator erase(iterator first, iterator last)
			{
				size_type n = this->distance(first, last);
				size_type index = this->distance(this->begin(), first);
				
				for (size_type i = index; i < this->_size - n; ++i) /* Move everything to the left by 1 from index */
				{
					this->_alloc.destroy(this->_ptr + i);
					this->_alloc.construct(this->_ptr + i, this->_ptr[i + n]);
				}
				this->_alloc.destroy(this->_ptr + this->_size - n);
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

			allocator_type get_allocator()
			{
				return (allocator_type());
			}

			/* Iterator */
			/* See https://gist.github.com/jeetsukumaran/307264 */
			class iterator : public ft::iterator<ft::random_access_iterator_tag, T> /* Only define 2 types since the 3 other default values are those we want */
			{
				private:
					typedef typename ft::vector<T>::size_type				size_type;
					typedef iterator										self_type; /* Used to that we can copypasta for const_iterator and modify only here */
					typedef ft::iterator<ft::random_access_iterator_tag, T>	it;
				
				public:
					typedef typename it::iterator_category					iterator_category;
					typedef typename it::value_type							value_type;
					typedef typename it::difference_type					difference_type;
					typedef typename it::pointer							pointer;
					typedef typename it::reference							reference;

				public:
					iterator(pointer ptr) : _ptr(ptr) { }

					self_type&	operator++() /* prefix */
					{
						++this->_ptr;
						return (*this);
					}

					self_type	operator++(int) /* postfix, cannot return reference to stack memory */
					{
						self_type tmp = *this;
						++(*this); /* so that if we want to change code, only change the prefix one */
						return (tmp);
					}

					self_type&	operator--() /* prefix */
					{
						--this->_ptr;
						return (*this);
					}

					self_type	operator--(int) /* postfix, cannot return reference to stack m */
					{
						self_type tmp = *this;
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

					self_type	operator+(difference_type n)
					{
						self_type tmp = *this;
						tmp._ptr += n;
						return (tmp);
					}

					self_type	operator+(const self_type& r)
					{
						self_type tmp = *this;
						tmp._ptr += r._ptr;
						return (tmp);
					}

					self_type&	operator+=(difference_type n)
					{
						this->_ptr += n;
						return (*this);
					}

					self_type	operator-(difference_type n)
					{
						self_type tmp = *this;
						tmp._ptr -= n;
						return (tmp);
					}

					self_type	operator-(const self_type& r)
					{
						self_type tmp = *this;
						tmp._ptr -= r._ptr;
						return (tmp);
					}

					self_type&	operator-=(difference_type n)
					{
						this->_ptr -= n;
						return (*this);
					}

					/* Relational operators */
					friend bool	operator==(const self_type& rhs, const self_type& lhs)
					{
						return (rhs._ptr == lhs._ptr);
					}

					friend bool	operator!=(const self_type& rhs, const self_type& lhs)
					{
						return (!(rhs == lhs));
					}

					friend bool	operator>(const self_type& rhs, const self_type& lhs)
					{
						return (rhs > lhs);
					}

					friend bool	operator>=(const self_type& rhs, const self_type& lhs)
					{
						return (rhs >= lhs);
					}

					friend bool	operator<(const self_type& rhs, const self_type& lhs)
					{
						return (rhs < lhs);
					}

					friend bool	operator<=(const self_type& rhs, const self_type& lhs)
					{
						return (rhs <= lhs);
					}

				private:
					pointer	_ptr;
			};

			/* Const iterator, almost the same as iterator */
			/* See https://gist.github.com/jeetsukumaran/307264 */
			class const_iterator : public ft::iterator<ft::random_access_iterator_tag, const T> /* Only define 2 types since the 3 other default values are those we want */
			{
				private:
					typedef typename vector<T>::size_type							size_type;
					typedef const_iterator											self_type; /* Used to that we can copypasta for const_iterator and modify only here */
					typedef ft::iterator<ft::random_access_iterator_tag, const T>	it;
				
				public:
					typedef typename it::iterator_category							iterator_category;
					typedef const typename it::value_type							value_type;
					typedef const typename it::difference_type						difference_type;
					typedef const typename it::pointer								pointer;
					typedef const typename it::reference							reference;

				public:
					const_iterator(T* ptr) : _ptr(ptr) { }

					self_type&	operator++() /* prefix */
					{
						++this->_ptr;
						return (*this);
					}

					self_type	operator++(int) /* postfix, cannot return reference to stack memory */
					{
						self_type tmp = *this;
						++(*this); /* so that if we want to change code, only change the prefix one */
						return (tmp);
					}

					self_type&	operator--() /* prefix */
					{
						--this->_ptr;
						return (*this);
					}

					self_type	operator--(int) /* postfix, cannot return reference to stack m */
					{
						self_type tmp = *this;
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

					self_type	operator+(difference_type n)
					{
						self_type tmp = *this;
						tmp._ptr += n;
						return (tmp);
					}

					self_type	operator+(const self_type& r)
					{
						self_type tmp = *this;
						tmp._ptr += r._ptr;
						return (tmp);
					}

					self_type&	operator+=(difference_type n)
					{
						this->_ptr += n;
						return (*this);
					}

					self_type	operator-(difference_type n)
					{
						self_type tmp = *this;
						tmp._ptr -= n;
						return (tmp);
					}

					self_type	operator-(const self_type& r)
					{
						self_type tmp = *this;
						tmp._ptr -= r._ptr;
						return (tmp);
					}

					self_type&	operator-=(difference_type n)
					{
						this->_ptr -= n;
						return (*this);
					}

					/* Relational operators */
					friend bool	operator==(const self_type& rhs, const self_type& lhs)
					{
						return (rhs._ptr == lhs._ptr);
					}

					friend bool	operator!=(const self_type& rhs, const self_type& lhs)
					{
						return (!(rhs == lhs));
					}

					friend bool	operator>(const self_type& rhs, const self_type& lhs)
					{
						return (rhs > lhs);
					}

					friend bool	operator>=(const self_type& rhs, const self_type& lhs)
					{
						return (rhs >= lhs);
					}

					friend bool	operator<(const self_type& rhs, const self_type& lhs)
					{
						return (rhs < lhs);
					}

					friend bool	operator<=(const self_type& rhs, const self_type& lhs)
					{
						return (rhs <= lhs);
					}

				private:
					T*	_ptr;
			};

	};

	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	/* We are not forced to write template arguments since compiler template
	   deduction does it automatically */
	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs)); /* Either <= or > */
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs)); /* Either < or >= */
	}

}

#endif