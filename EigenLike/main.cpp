#include "el.hpp"
#include <eigen3/Eigen/Core>
#include <iostream>

int main(void) {
	el::vector<double,3> v;
	double a = 1;
	v << 2, 3, 4;
	std::cout << "a = " << a << std::endl << std::endl;
	a = v.x();
	v.x() = 5;
	std::cout << "v = " << std::endl << v << std::endl;
	std::cout << "a = " << a << std::endl << std::endl;

	el::matrix<double, 4, 4> m, y, g;
	std::cout << "m = " << std::endl << m << std::endl;
	y = el::matrix<double, 4, 4>::identity();
	g = el::matrix<double, 4, 4>::identity(4);
	m << 3, 1, 4, 1,
		5, 9, 2, 6,
		5, 3, 5, 8,
		9, 7, 9, 3;
	std::cout << "m = " << std::endl << m << std::endl;
	std::cout << "y = " << std::endl << y << std::endl;
	std::cout << "g = " << std::endl << g << std::endl;
	std::cout << "m + y + g = " << std::endl << m + y + g << std::endl;
	std::cout << "m - y - g = " << std::endl << m - y - g << std::endl;
	std::cout << "m - y + g = " << std::endl << m - y + g << std::endl;
	std::cout << "m * m = " << std::endl << m * m << std::endl;
	std::cout << "m * m * m = " << std::endl << m * m * m << std::endl;
	std::cout << "2 * m * m + 4 * y - m / 8 = " << std::endl << 2 * m * m + 4 * y - m / 8 << std::endl;
	std::cout << "m * 3 * 4 = " << std::endl << m * 3 * 4 << std::endl << std::endl;

	el::matrix<double, 3, 3> x;
	x << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	std::cout << "x = " << std::endl << x << std::endl;
	x *= 4;
	std::cout << "x *= 4" << std::endl << "x =" << std::endl << x << std::endl;
	std::cout << "x =" << std::endl << x << std::endl;
	x /= 5;
	std::cout << "x /= 5" << std::endl << "x =" << std::endl << x << std::endl << std::endl;

	std::cout << "m = " << std::endl << m << std::endl;
	m *= m;
	std::cout << "m *= m" << std::endl << "m =" << std::endl << m << std::endl;

	el::K<double> k;
	std::cout << "K = " << std::endl << k << std::endl;
	k.fx() = 1280.1241241;
	k.fy() = 800.1241446345623;
	k.ppx() = 640.867452452;
	k.ppy() = 400.568462;
	std::cout << "K = " << std::endl << k << std::endl;
	k.identity();
	std::cout << "K = " << std::endl << k << std::endl;
	std::cout << "K size = " << k.size() << std::endl << "K rows = " << k.rows() <<  std::endl << "K cols = " << k.cols() << std::endl;
}
