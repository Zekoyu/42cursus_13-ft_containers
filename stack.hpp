/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 02-03-2022 10:35 by                                             */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <vector.hpp>

namespace ft
{

	template < class T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container	c; /* Don't name it _c to follow original naming */

		public:
			typedef T								value_type;
			typedef Container						container_type;
			typedef typename Container::size_type	size_type;

			/* takes either a container (default vector) and initialize the underlying container (vector) with it
			   if nothing is provided, will create an empty vector (default value : "= container_type()") */
			explicit stack (const container_type& cont = container_type()) : c(cont) { }
			stack(const stack& s) : c(s.c) { }

			bool		empty() const { return (this->c.empty()); }
			size_type	size() const { return (this->c.size()); }

			value_type			&top() { return (this->c.back()); }
			value_type const	&top() const  { return (this->c.back()); }
			void 				push(const value_type& val) { this->c.push_back(val); }
			void				pop() { this->c.pop_back(); }

			stack&	operator= (const stack& other)
			{
				this->c = other.c;
				return (*this);
			}

			/* In class definition, friend keyword followed by a function definition defines it as non-member of the class and friend at the same time
			   easier to write than "friend bool operator== ..." and implementation outside the class (which would be exactly the same thing) 
			   
			   Advantages of using non-member overload (rhs + lhs) instead of member (only rhs) is that we can do, taking double as exemple:
			   s1 + s2 AND s2 + s1 instead of only s1 + s2 */
			friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c == rhs.c); }
				
			friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c != rhs.c); }

			friend bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c < rhs.c); }

			friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c <= rhs.c); }

			friend bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c > rhs.c); }

			friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return(lhs.c >= rhs.c); }
	};
	
}

#endif