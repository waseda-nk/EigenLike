#include "el.hpp"
#include <iostream>

int main(void) {
	el::vector<double,3> v;
	double a = 1;
	v << 2, 3, 4;
	std::cout << a << std::endl;
	a = v.x();
	v.x() = 5;
	std::cout << v << std::endl;
	std::cout << a << std::endl << std::endl;

	el::matrix<double, 4, 4> m, y, g;
	std::cout << m << std::endl;
	y = el::matrix<double, 4, 4>::identity();
	g = el::matrix<double, 4, 4>::identity(4);
	m << 3, 1, 4, 1,
		5, 9, 2, 6,
		5, 3, 5, 8,
		9, 7, 9, 3;
	std::cout << m << std::endl;
	std::cout << y << std::endl;
	std::cout << g << std::endl;
	std::cout << m + y + g << std::endl;
	std::cout << m - y - g << std::endl;
	std::cout << m - y + g << std::endl;

	el::K<double> k;
	std::cout << k << std::endl;
	k.fx() = 1280.1241241;
	k.fy() = 800.1241446345623;
	k.ppx() = 640.867452452;
	k.ppy() = 400.568462;
	std::cout << k << std::endl;
	k.identity();
	std::cout << k << std::endl;
	std::cout << k.size() << "  " << k.rows() << "  " << k.cols() << "  " << std::endl;
}