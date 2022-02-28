/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 28-02-2022 15:42 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <vector>
// TODO CHANGE THIS TO FT VECTOR

namespace ft
{
	template < class T, class Container = std::vector<T> >
	class stack
	{
		private:
			Container	_c;

		public:
			typedef T								value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;

			/* takes either a container (default vector) and initialize the underlying container (vector) with it
			   if nothing is provided, will create an empty vector (default value : "= container_type()") */
			explicit stack (const container_type& cont = container_type()) : _c(cont) { }
			stack(const stack& s) : _c(s._c) { }

			bool		empty() const { return (this->_c.empty()); }
			size_type	size() const { return (this->_c.size()); }

			value_type			&top() { return (this->_c.back()); }
			value_type const	&top() const  { return (this->_c.back()); }
			void 				push(const value_type& val) { this->_c.push_back(val); }
			void				pop() { this->_c.pop_back(); }

			stack&	operator= (const stack& other)
			{
				this->_c = other._c;
				return (*this);
			}

			/* In class definition, friend keyword followed by a function definition defines it as non-member of the class and friend at the same time
			   easier to write than "friend bool operator== ..." and implementation outside the class (which would be exactly the same thing) */
			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c == rhs._c); }
				
			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c != rhs._c); }

			friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c < rhs._c); }

			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c <= rhs._c); }

			friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c > rhs._c); }

			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs._c >= rhs._c); }
	};


	
}

#endif