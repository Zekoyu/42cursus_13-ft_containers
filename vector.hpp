/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 03-03-2022 15:46 by                                             */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include "iterators.hpp"

namespace ft
{

	// > > instead of >> because otherwise C++ might think it's a bitshift
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T								value_type;
			typedef Allocator						allocator_type;
			/* All of these could be used with value_type for the default allocator, but maybe not custom ones */
			typedef allocator_type::reference		reference; /* Same as value_type& */
			typedef allocator_type::const_reference	const_reference; /* Same as const value_type& */
			typedef allocator_type::pointer			pointer; /* Same as value_type* */
			typedef allocator_type::const_pointer	const_pointer; /* Same as const value_type* */
			typedef size_t							size_type; /* Enough to hold any positive integral type (integer) */
			
			/* InIterator, OutIterator, ForIterator, BiIterator, RandIterator
			   These are generic type names used for (respectively) input iterators, output iterators, forward iterators, bidirectional iterators, and random access iterators.
			   For example, vector<int>::iterator is a RandIterator, while list<string>::iterator is a BiIterator. */
			class RandIterator : public ft::iterator<ft::random_access_iterator_tag, T> /* Only define 2 types since the 3 other default values are those we want */
			{
				public:
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
					RandIterator::reference	operator[](size_type index)
					{
						return (*(this->_ptr[index]));
					}

					/* Calling Foo->x becomes the same as Foo.operator->()->x  or *(Foo.operator->()x)
					   The compiler calls the operator -> as many times as needed to get a raw pointer, then dereferences it */
					RandIterator::pointer	operator->()
					{
						return (this->_ptr);
					}

					RandIterator::reference	operator*()
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
					
				private:
					pointer	_ptr;
			}
			
	};
	
}
