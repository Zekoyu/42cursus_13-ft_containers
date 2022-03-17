#include <iostream>

template <typename T>
void pouet(typename T::value_type val)
{
	std::cout << "Value pouet " << val << std::endl;
	return ;
}

/* By coimmenting this function template the code will not compile because there are no other matching templates */
template <typename T>
void pouet (T pouet)
{
	std::cout << "Generic pouet" << std::endl;
}

struct Example
{
	typedef int value_type;
};


int main()
{
	pouet<Example>(123);
	pouet<int>(10); /* Substitution failure in first one (T::value_type) , but not an error */
	
}