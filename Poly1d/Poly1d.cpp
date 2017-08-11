#include "Poly1d.h"
#include <cmath>
#include <iomanip>
#include <ostream>
#include <iostream>

template <typename T>
bool is_zero(T val, double epsilon = 1e-7) {
	return std::fabs(val) < epsilon;
}

Poly1d::Poly1d(const std::vector<double>& coeffs) {
	if (coeffs.empty()) {
		coeffs_.push_back(0);
		order_ = 0;
		size_ = 1;
	}
	else {
		std::vector<double> tmp = coeffs;
		while (is_zero(tmp[0]) && tmp.size() > 1) {
			tmp.erase(tmp.begin());
		}
		size_ = tmp.size();
		coeffs_ = tmp;
		order_ = size_ - 1;
	}

	variable_ = std::string("x");
}

std::vector<double> Poly1d::coeffs() const {
	return coeffs_;
}

int Poly1d::order() const {
	return order_;
}

double Poly1d::operator()(double x) const {
	return evalPolynomial_(x);
}

double Poly1d::evalPolynomial_(double x) const {
	double val = 0;
	for (int i = 0; i < size_; ++i) {
		val += coeffs_[i] * std::pow(x, size_ - 1 - i);
	}
	return val;
}

double Poly1d::operator[](int n) const {
	int index = size_ - 1 - n;
	if (0 <= index && index < size_) {
		return coeffs_[index];
	}
	else {
		/* 範囲外の場合はその次数の項の係数は 0 とする */
		return 0;
	}
}

std::ostream& operator<<(std::ostream& ost, const Poly1d& obj) {
	for (int n = obj.order_; n >= 0; --n) {
		if (is_zero(obj[n])){
			/* 係数が 0 なら表示しない */
			continue;
		}
		else {
			if (n != obj.order_) {
				if (obj[n] > 0) {
					ost << " + ";
				}
				else {
					ost << " - ";
				}
			}
			ost << std::fabs(obj[n]);
			if (n > 1) {
				ost << " " << obj.variable_ << "^" << n;
			}
			else if (n == 1) {
				ost << " " << obj.variable_;
			}
		}
	}
	return ost;
}

std::vector<cv::Vec2d> Poly1d::roots() const {
	return getRoots_();
}

std::vector<double> Poly1d::rootsReal(double epsilon) const {
	/* 虚数根も含めて根を求める */
	std::vector<cv::Vec2d> tmp = getRoots_();
	std::vector<double> real_roots;
	for each (cv::Vec2d root in tmp) {
		/* root[0]: 実部, root[1]: 虚部 */
		if (is_zero(root[1], epsilon)) {
			real_roots.push_back(root[0]);
		}
	}
	return real_roots;
}

std::vector<cv::Vec2d> Poly1d::getRoots_() const {
	/* solvePoly に渡す多項式係数は、低次から順に格納する必要がある */
	std::vector<double> tmp = coeffs_;
	std::reverse(tmp.begin(), tmp.end());
	std::vector<cv::Vec2d> result;
	cv::solvePoly(tmp, result);
	return result;
}