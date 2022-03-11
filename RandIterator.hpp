/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 10-03-2022  by  `-'                        `-'                  */
/*   Updated: 11-03-2022 10:14 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDITERATOR_HPP
# define RANDITERATOR_HPP

#include "iterators.hpp"
#include "utils.hpp"
#include "enable_if.hpp"

namespace ft
{
	/* https://quuxplusone.github.io/blog/2018/12/01/const-iterator-antipatterns/ */
	/* https://stackoverflow.com/questions/2150192/how-to-avoid-code-duplication-implementing-const-and-non-const-iterators */
	/* We keep T as non const, and in functions needing const we add it manually */
	template <class T, bool IsConst = false>
	class RandIterator
	{
		private:
			/* If const, type is an iterator over const T, otherwise only over T */
			typedef typename ft::choose<IsConst, ft::iterator<ft::random_access_iterator_tag, const T>,
										ft::iterator<ft::random_access_iterator_tag, T> >::type iterator;
			
		public:
			typedef RandIterator<T, IsConst> self_type;

		public:
			typedef typename iterator::iterator_category	iterator_category;
			typedef typename iterator::value_type			value_type;
			typedef typename iterator::reference			reference;
			typedef typename iterator::pointer				pointer;

			typedef ptrdiff_t	difference_type;
			typedef size_t		size_type;

			RandIterator(pointer ptr) : _ptr(ptr) { }

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

			self_type&	operator=(const self_type &rhs)
			{
				this->_ptr = rhs._ptr;
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
}

#endif