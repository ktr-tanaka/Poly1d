/**
  @file
  @brief Poly1d �N���X�̃e�X�g�R�[�h
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

	/* ������Z�q������ˁH */
	Poly1d poly2 = poly1;
	std::cout << poly2 << std::endl;
	
	/* �R�s�[�R���X�g���N�^�́H */
	Poly1d poly3(std::vector<double>(6));
	std::cout << "poly3: " << poly3 << std::endl;
	poly3 = poly1;
	std::cout << poly3 << std::endl;

	/* �тԂ�` */
	std::cout << poly1.deriv() << std::endl;
	/* �Ɂ`���`���`�с`�ԁ`��`�`�`�` */
	std::cout << poly1.deriv(2) << std::endl;
	/* ���`���`���`(ry*/
	std::cout << poly1.deriv(3) << std::endl;
	Poly1d check = poly1.deriv(3);

	std::cout << poly1.integ(1, 2) << std::endl;
	std::cout << poly1.integ(3, 2) << std::endl;
	std::vector<double> k = { 1,2, 3 };
	std::cout << poly1.integ(3, k) << std::endl;

	std::cout << Poly1d(4) << std::endl;
	std::cout << -poly1 << std::endl;
}

