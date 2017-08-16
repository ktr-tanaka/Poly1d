/**
  @file
  @brief Poly1d �N���X�̃e�X�g�R�[�h
*/

#include "Poly1d.h"
#include <iostream>
#include <vector>
#include <cstdio>

template <typename T>
static void print_contents_of_vector(const std::vector<T>& vec) {
	for (size_t i = 0, size = vec.size(); i < size; ++i) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
};

int main() {
	/* �R���X�g���N�^ */
	std::vector<double> coeffs = {1, -3, -1, 3};
	Poly1d p1(coeffs);
	std::cout << p1 << std::endl;
	Poly1d p1_t(coeffs, false, "hoge");
	std::cout << p1_t << std::endl;
	std::vector<double> roots = { -1, 1, 3 };
	Poly1d p1_by_root(roots, true);
	std::cout << p1_by_root << std::endl;

	/* ����l�𑽍����Ŏʂ����l��Ԃ� */
	std::printf("4.0 -> %.1f\n", p1(4.0));

	/* �W���A�����𓾂� */
	std::vector<double> c = p1.coeffs(); // �W��
	double a2 = p1[2]; // �񎟂̌W��
	double n = p1.order(); // �������̎���

	/* ���Z�A���Z�A��Z */
	std::vector<double> coeffs2 = { -2, 2, 4 };
	Poly1d p2(coeffs2);
	std::cout << "p1: " << p1 << std::endl;
	std::cout << "p2: " << p2 << std::endl;
	std::cout << "+ : " << p1 + p2 << std::endl;
	std::cout << "- : " << p1 - p2 << std::endl;
	std::cout << "* : " << p1 * p2 << std::endl;

	/* ���Z */
	std::cout << "p1: " << p1 << std::endl;
	std::cout << "p2: " << p2 << std::endl;
	std::vector<Poly1d> division_result = p1 / p2;
	std::cout << "���@: " << division_result[0] << std::endl;
	std::cout << "��]: " << division_result[1] << std::endl;

	/* �������߂� */
	std::vector<double> coeffs3 = {1, -2, 3};
	Poly1d p3(coeffs3);
	std::vector<cv::Vec2d> result1 = (p1 * p3).roots();
	print_contents_of_vector(result1);

	/* �������̂� */
	std::vector<double> result2 = (p1 * p3).rootsReal();
	print_contents_of_vector(result2);

	/* ���� */
	std::cout << p1 << std::endl
              << p1.deriv() << std::endl
              << p1.deriv(2) << std::endl
              << p1.deriv(3) << std::endl
              << p1.deriv(4) << std::endl;

	/* �s��ϕ� */
	std::cout << p1 << std::endl
		<< p1.integ(1) << std::endl
		<< p1.integ(2) << std::endl;

	/* �s��ϕ��i�ϕ��萔�w��j */
	std::cout << p1.integ(1, 100) << std::endl;
	std::vector<double> consts = { 100, 200 };
	std::cout << p1.integ(2, consts) << std::endl;

	/* �ŋߖT�_�Ƌ��� */
	std::cout << p1 << std::endl;
	cv::Point2d p(2, 0);
	cv::Point2d nearest;
	double nearest_dist = p1.nearestPoint(p, nearest);
	std::cout << nearest_dist << ", " << nearest << std::endl;

}

