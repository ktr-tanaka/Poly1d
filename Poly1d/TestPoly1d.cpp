/**
  @file
  @brief Poly1d ƒNƒ‰ƒX‚ÌƒeƒXƒgƒR[ƒh
*/

#include "Poly1d.h"
#include <iostream>
#include <vector>

template <typename T>
static void print_contents_of_vector(const std::vector<T>& vec) {
	for (size_t i = 0, size = vec.size(); i < size; ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
};

int main() {
	std::vector<double> coefs = {
		1, -3, -1, 3
	};

	Poly1d poly1(coefs);
	
	std::vector<double> returned_coefs = poly1.coeffs();
	print_contents_of_vector(returned_coefs);

	std::cout << "order: " << poly1.order() << std::endl;

	std::cout << poly1(3.5) << std::endl;

	std::cout << poly1[2] << std::endl;
	std::cout << poly1[-100] << std::endl;

	std::cout << poly1 << std::endl;

	print_contents_of_vector(poly1.roots());
	print_contents_of_vector(poly1.rootsReal());

	/* ‘ã“ü‰‰Zq“­‚­‚æ‚ËH */
	Poly1d poly2 = poly1;
	std::cout << poly2 << std::endl;
	
	/* ƒRƒs[ƒRƒ“ƒXƒgƒ‰ƒNƒ^‚ÍH */
	Poly1d poly3(std::vector<double>(6));
	std::cout << "poly3: " << poly3 << std::endl;
	poly3 = poly1;
	std::cout << poly3 << std::endl;

	/* ‚Ñ‚Ô‚ñ` */
	std::cout << poly1.deriv() << std::endl;
	/* ‚É`‚©`‚¢`‚Ñ`‚Ô`‚ñ```` */
	std::cout << poly1.deriv(2) << std::endl;
	/* ‚²`‚©`‚¢`(ry*/
	std::cout << poly1.deriv(3) << std::endl;
	Poly1d check = poly1.deriv(3);

	std::cout << poly1.integ(1, 2) << std::endl;
	std::cout << poly1.integ(3, 2) << std::endl;
	std::vector<double> k = { 1,2, 3 };
	std::cout << poly1.integ(3, k) << std::endl;

	std::cout << Poly1d(4) << std::endl;
	std::cout << -poly1 << std::endl;

	std::cout << poly1 + poly1 << std::endl;
	std::cout << poly1 - poly1 << std::endl;
	std::cout << poly1 + 5 << std::endl;
	std::cout << 5 + poly1 << std::endl;
	std::cout << poly1 - 5 << std::endl;
	std::cout << 5 - poly1 << std::endl;
	std::cout << 5 + (-poly1) << std::endl;

	std::cout << poly1 * poly1 << std::endl;

	std::vector<double> poly4_coeffs = { 2, -3, -1, 3 };
	Poly1d poly4(poly4_coeffs);
	print_contents_of_vector(poly1 / poly4);

	std::cout << poly1 << std::endl;
	std::cout << poly1 * 10 << std::endl;
	std::cout << poly1 / 10 << std::endl;

	std::cout << poly1 << std::endl;
	cv::Point2d p(2, 0);
	cv::Point2d nearest;
	double nearest_dist = poly1.nearestPoint(p, nearest);
	std::cout << nearest_dist << ", " << nearest << std::endl;

	cv::Point2d nearest_check;
	double nearest_dist_check = poly1.nearestPoint(nearest, nearest_check);
	std::cout << nearest_dist_check << ", " << nearest_check << std::endl;

	std::vector<double> test1_coeffs = { 1,2,3,4 };
	Poly1d test1(test1_coeffs);
	std::cout << test1 << std::endl;
	Poly1d test2(test1_coeffs, false, "t");
	std::cout << test2 << std::endl;
	std::vector<double> test2_roots = { 1,2,3 };
	Poly1d test3(test2_roots, true);
	std::cout << test3 << std::endl;
	Poly1d test4(test2_roots, true, "t");
	std::cout << test4 << std::endl;

	std::cout << Poly1d(4) << std::endl;
	std::cout << Poly1d(4, true, "t") << std::endl;
}

