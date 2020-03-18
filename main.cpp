#include "el.hpp"
#include <iostream>

int main(void) {
	el::vector<double, 3> v;
	double a = 1;
	v << 1, 3, 4;
	std::cout << a << std::endl;
	a = v(2);
	std::cout << v(0) << "  " << v(1) << "  " << v(2) << std::endl;
	std::cout << a << std::endl;
}