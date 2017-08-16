/**
  @file
  @brief Poly1d クラスのテストコード
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
	/* コンストラクタ */
	std::vector<double> coeffs = {1, -3, -1, 3};
	Poly1d p1(coeffs);
	std::cout << p1 << std::endl;
	Poly1d p1_t(coeffs, false, "hoge");
	std::cout << p1_t << std::endl;
	std::vector<double> roots = { -1, 1, 3 };
	Poly1d p1_by_root(roots, true);
	std::cout << p1_by_root << std::endl;

	/* ある値を多項式で写した値を返す */
	std::printf("4.0 -> %.1f\n", p1(4.0));

	/* 係数、次数を得る */
	std::vector<double> c = p1.coeffs(); // 係数
	double a2 = p1[2]; // 二次の係数
	double n = p1.order(); // 多項式の次数

	/* 加算、減算、乗算 */
	std::vector<double> coeffs2 = { -2, 2, 4 };
	Poly1d p2(coeffs2);
	std::cout << "p1: " << p1 << std::endl;
	std::cout << "p2: " << p2 << std::endl;
	std::cout << "+ : " << p1 + p2 << std::endl;
	std::cout << "- : " << p1 - p2 << std::endl;
	std::cout << "* : " << p1 * p2 << std::endl;

	/* 除算 */
	std::cout << "p1: " << p1 << std::endl;
	std::cout << "p2: " << p2 << std::endl;
	std::vector<Poly1d> division_result = p1 / p2;
	std::cout << "商　: " << division_result[0] << std::endl;
	std::cout << "剰余: " << division_result[1] << std::endl;

	/* 根を求める */
	std::vector<double> coeffs3 = {1, -2, 3};
	Poly1d p3(coeffs3);
	std::vector<cv::Vec2d> result1 = (p1 * p3).roots();
	print_contents_of_vector(result1);

	/* 実数痕のみ */
	std::vector<double> result2 = (p1 * p3).rootsReal();
	print_contents_of_vector(result2);

	/* 微分 */
	std::cout << p1 << std::endl
              << p1.deriv() << std::endl
              << p1.deriv(2) << std::endl
              << p1.deriv(3) << std::endl
              << p1.deriv(4) << std::endl;

	/* 不定積分 */
	std::cout << p1 << std::endl
		<< p1.integ(1) << std::endl
		<< p1.integ(2) << std::endl;

	/* 不定積分（積分定数指定） */
	std::cout << p1.integ(1, 100) << std::endl;
	std::vector<double> consts = { 100, 200 };
	std::cout << p1.integ(2, consts) << std::endl;

	/* 最近傍点と距離 */
	std::cout << p1 << std::endl;
	cv::Point2d p(2, 0);
	cv::Point2d nearest;
	double nearest_dist = p1.nearestPoint(p, nearest);
	std::cout << nearest_dist << ", " << nearest << std::endl;

}

