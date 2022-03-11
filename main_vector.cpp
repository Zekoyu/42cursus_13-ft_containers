/* ************************************************************************** */
/*                                                                            */
/*                                  .-.                       .               */
/*                                 / -'                      /                */
/*                  .  .-. .-.   -/--).--..-.  .  .-. .-.   /-.  .-._.)  (    */
/*   By:             )/   )   )  /  /    (  |   )/   )   ) /   )(   )(    )   */
/*                  '/   /   (`.'  /      `-'-''/   /   (.'`--'`-`-'  `--':   */
/*   Created: 28-02-2022  by  `-'                        `-'                  */
/*   Updated: 11-03-2022 16:42 by                                             */
/*                                                                            */
/* ************************************************************************** */

//#include "stack.hpp"
//#include <iostream>
//#include "iterator_traits.hpp"
//#include "vector.hpp"
#include <vector>
#include <iostream>
#include "vector.hpp"


#define VECTOR_TYPE	int
#define LIB			ft

template <typename Vector>
void	print_vector(Vector v)
{
	std::cout << "Vector content: ";
	for (typename Vector::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

template <typename Vector>
void	reverse_print_vector(Vector v)
{
	std::cout << "Reverse vector content: ";
	for (typename Vector::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

/* Tests all functions:

	- begin, end, rbegin, rend

	- size, max_size, resize, capacity, empty, reserve

	- operator[], at, front, back

	- assign, push_back, pop_back, insert, erase, swap, clear

	- get_allocator
*/

template < typename Vector >
void	test_vector(Vector v)
{
	//typedef typename Vector::iterator iterator;
	//typedef typename Vector::value_type value_type;

	std::cout << "POUET\n";
	std::cout << "Vector max potential size: " << v.max_size() << std::endl;
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << "Empty ? " << v.empty() << std::endl << std::endl;

	std::cout << "Pushing 1, 2 and 3" << std::endl;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << "Empty ? " << v.empty() << std::endl;
	print_vector(v);
	reverse_print_vector(v);
	std::cout << std::endl;

	std::cout << "Resizing vector to 10" << std::endl;
	v.resize(10);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	print_vector(v);
	std::cout << std::endl;

	std::cout << "Reserving 123" << std::endl;
	v.reserve(123);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	print_vector(v);
	std::cout << std::endl;

	std::cout << "Printing first and second element using operator[]" << std::endl;
	std::cout << "First: " << v[0] << ", second: " << v[1] << std::endl << std::endl;

	std::cout << "Using at on element at index 1 and 9999" << std::endl;
	try
	{
		std::cout << "Index 1: " << std::endl;
		std::cout << v.at(1) << std::endl << std::endl;
		std::cout << "Index 9999:" << std::endl;
		std::cout << v.at(9999) << std::endl << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Accessing front and back" << std::endl;
	std::cout << "Front: " << v.front() << ", back: " << v.back() << std::endl << std::endl;

	std::cout << "Testing 2 versions of assign" << std::endl;
	std::cout << "Assigning 5 times 321" << std::endl;
	v.assign(5, 321);
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	{
	std::vector<VECTOR_TYPE> tmp(3, 100);
	std::cout << "Assigning vector(100, 100, 100) begin and end" << std::endl;
	v.template assign<std::vector<VECTOR_TYPE>::iterator>(tmp.begin(), tmp.end()); /* cannot compile without template */
	}
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << std::endl;

	std::cout << "Pop back 2 times" << std::endl;
	v.pop_back();
	v.pop_back();
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl << std::endl;

	std::cout << "Testing 3 versions of insert" << std::endl;
	std::cout << "Inserting -42 at begin" << std::endl;
	v.insert(v.begin(), -42);
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << "Inserting 3 times 99 at end" << std::endl;
	v.insert(v.end(), 3, 99);
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << "Inserting vector(1, 2, 3) begin and end at begin + 1" << std::endl;
	{
		std::vector<VECTOR_TYPE> tmp;
		tmp.push_back(1);
		tmp.push_back(2);
		tmp.push_back(3);
		v.template insert<std::vector<VECTOR_TYPE>::iterator>(v.begin() + 1, tmp.begin(), tmp.end()); /* template keyword to compile */
	}
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl << std::endl;

	std::cout << "Erasing begin + 2" << std::endl;
	v.erase(v.begin() + 2);
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
	std::cout << "Erasing from begin + 1 to end - 2" << std::endl;
	v.erase(v.begin() + 1, v.end() - 2);
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl << std::endl;

	std::cout << "Swapping vector with vector(1, 2, 3) using vector.swap(x)" << std::endl;
	{
		Vector v2;

		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(3);

		std::cout << "Before swap" << std::endl;
		print_vector(v);
		std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
		std::cout << "V2" << std::endl;
		print_vector(v2);
		std::cout << "Capacity=" << v2.capacity() << ", Size=" << v2.size() << std::endl << std::endl;
		v.swap(v2);
		std::cout << "After swap" << std::endl;
		print_vector(v);
		std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
		std::cout << "V2" << std::endl;
		print_vector(v2);
		std::cout << "Capacity=" << v2.capacity() << ", Size=" << v2.size() << std::endl << std::endl;
		v.swap(v2);
	}

	std::cout << "Swapping vector with vector(1, 2, 3) using non-member function ::swap(x, y)" << std::endl;
	{
		Vector v2;

		v2.push_back(1);
		v2.push_back(2);
		v2.push_back(3);

		std::cout << "Before swap" << std::endl;
		print_vector(v);
		std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
		std::cout << "V2" << std::endl;
		print_vector(v2);
		std::cout << "Capacity=" << v2.capacity() << ", Size=" << v2.size() << std::endl << std::endl;
		LIB::swap(v, v2);
		std::cout << "After swap" << std::endl;
		print_vector(v);
		std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl;
		std::cout << "V2" << std::endl;
		print_vector(v2);
		std::cout << "Capacity=" << v2.capacity() << ", Size=" << v2.size() << std::endl << std::endl;
	}

	std::cout << "Testing all 6 relational operators (==, !=, >, >=, <, <=)" << std::endl;
	{
		Vector same = v;
		Vector smaller;
		Vector bigger;

		smaller = v;
		smaller.erase(smaller.begin());
		bigger = v;
		bigger.push_back(-1);
	
		std::cout << "Vector:" << std::endl;
		print_vector(v);
		std::cout << std::endl << "V1:" << std::endl;
		std::cout << "Capacity=" << same.capacity() << ", Size=" << same.size() << std::endl;
		print_vector(same);
		std::cout << std::endl << "V2:" << std::endl;
		std::cout << "Capacity=" << smaller.capacity() << ", Size=" << smaller.size() << std::endl;
		print_vector(smaller);
		std::cout << std::endl << "V3:" << std::endl;
		std::cout << "Capacity=" << bigger.capacity() << ", Size=" << bigger.size() << std::endl;
		print_vector(bigger);
		std::cout << std::endl;

		std::cout << "Vector == V1 ? " << std::boolalpha << (v == same) << std::endl;
		std::cout << "Vector != V1 ? " << std::boolalpha << (v != same) << std::endl;
		std::cout << "Vector < V1 ? " << std::boolalpha << (v < same) << std::endl;
		std::cout << "Vector <= V1 ? " << std::boolalpha << (v <= same) << std::endl;
		std::cout << "Vector > V1 ? " << std::boolalpha << (v > same) << std::endl;
		std::cout << "Vector >= V1 ? " << std::boolalpha << (v >= same) << std::endl;
		std::cout << std::endl;
		std::cout << "Vector == V2 ? " << std::boolalpha << (v == smaller) << std::endl;
		std::cout << "Vector != V2 ? " << std::boolalpha << (v != smaller) << std::endl;
		std::cout << "Vector < V2 ? " << std::boolalpha << (v < smaller) << std::endl;
		std::cout << "Vector <= V2 ? " << std::boolalpha << (v <= smaller) << std::endl;
		std::cout << "Vector > V2 ? " << std::boolalpha << (v > smaller) << std::endl;
		std::cout << "Vector >= V2 ? " << std::boolalpha << (v >= smaller) << std::endl;
		std::cout << std::endl;
		std::cout << "Vector == V3 ? " << std::boolalpha << (v == bigger) << std::endl;
		std::cout << "Vector != V3 ? " << std::boolalpha << (v != bigger) << std::endl;
		std::cout << "Vector < V3 ? " << std::boolalpha << (v < bigger) << std::endl;
		std::cout << "Vector <= V3 ? " << std::boolalpha << (v <= bigger) << std::endl;
		std::cout << "Vector > V3 ? " << std::boolalpha << (v > bigger) << std::endl;
		std::cout << "Vector >= V3 ? " << std::boolalpha << (v >= bigger) << std::endl;
		std::cout << std::endl;
	}

	 std::cout << "Testing all 4 constructors:" << std::endl;
	{
		std::cout << "Default constructor:" << std::endl;

		Vector v1;
		print_vector(v1);
		std::cout << "Capacity=" << v1.capacity() << ", Size=" << v1.size() << std::endl << std::endl;
	}
	{
		std::cout << "Fill constructor (5, 100):" << std::endl;
		Vector v1(5, 100);
		print_vector(v1);
		std::cout << "Capacity=" << v1.capacity() << ", Size=" << v1.size() << std::endl << std::endl;

		std::cout << "Range constructor: (100, 100, 100, 100, 100)" << std::endl;
		Vector v2(v1.begin(), v1.end());
		print_vector(v2);
		std::cout << "Capacity=" << v2.capacity() << ", Size=" << v2.size() << std::endl << std::endl;
		 
		std::cout << "Copy constructor: (100, 100, 100, 100, 100)" << std::endl;
		Vector v3(v2);
		print_vector(v3);
		std::cout << "Capacity=" << v3.capacity() << ", Size=" << v3.size() << std::endl << std::endl;
	}

	std::cout << "Clearing vector" << std::endl;
	std::cout << "Before clear:" << std::endl;
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl << std::endl;
	v.clear();
	std::cout << "After clear:" << std::endl;
	print_vector(v);
	std::cout << "Capacity=" << v.capacity() << ", Size=" << v.size() << std::endl << std::endl;

	//v.get_allocator();
}

template <typename Iterator>
void	modifyContent(Iterator begin, Iterator end)
{
	while (begin != end)
	{
		*begin += 1;
		++begin;
	}
	std::cout << "Successfully modified content" << std::endl;
}

int main()
{
	typedef VECTOR_TYPE				vector_type;
	typedef ft::vector<vector_type>	vector;
	
	vector	v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	vector v1(v);

//	std::cout << "Len: " << (v1.end() - v1.begin()) << std::endl; 
	
	//test_vector<vector>(v);
	//modifyContent(v.begin(), v.end());
}