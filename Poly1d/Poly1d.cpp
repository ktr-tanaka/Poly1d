#include "Poly1d.h"
#include <cmath>
#include <iomanip>
#include <ostream>
#include <iostream>
#include <stdexcept>

template <typename T>
static bool is_zero(T val, double epsilon = 1e-7) {
	return std::fabs(val) < epsilon;
}

template <typename T>
static void invert_sign_of_vector(std::vector<T> vec) {
	for (size_t i = 0, size = vec.size; i < size; ++i) {
		vec[i] = -vec[i];
	}
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
	if (obj.order_ == 0) {
		ost << obj[0];
		return ost;
	}
	else {
		for (int n = obj.order_; n >= 0; --n) {
			if (is_zero(obj[n])) {
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
}

Poly1d Poly1d::operator+(double rop) const {
	std::vector<double> coeffs = this->coeffs_;
	coeffs[coeffs.size() - 1] += rop;
	return Poly1d(coeffs);
}

Poly1d operator+(double lop, const Poly1d& rop) {
	std::vector<double> coeffs = rop.coeffs_;
	coeffs[coeffs.size() - 1] += lop;
	return Poly1d(coeffs);
}

Poly1d Poly1d::operator-() const {
	std::vector<double> coeffs = this->coeffs_;
	invert_sign_of_vector(coeffs);
	return Poly1d(coeffs);
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

Poly1d Poly1d::deriv(int m) const {
	if (m < 0) {
		throw std::invalid_argument(
			"微分回数は 0 以上でなければなりません"
		);
	}
	Poly1d tmp = *this;
	for (int i = 0; i < m; ++i) {
		tmp = tmp.derivOnce_();
		if (tmp.order_ == 0 && is_zero(tmp[0])) {
			break;
		}
	}
	return tmp;
}

Poly1d Poly1d::integ(int m, double k) const{
	if (m < 0) {
		throw std::invalid_argument(
			"積分回数は 0 以上でなければなりません"
		);
	}
	Poly1d tmp = *this;
	for (int i = 0; i < m; ++i) {
		tmp = tmp.integOnce_(k);
	}
	return tmp;
}

Poly1d Poly1d::integ(int m, std::vector<double> k) const {
	if (m < 0) {
		throw std::invalid_argument(
			"積分回数は 0 以上でなければなりません"
		);
	}
	if (m > k.size()) {
		/* TODO vectorの領域は確保されているが中身が初期化されていないときのsize()の挙動は？ */
		throw std::invalid_argument(
			"積分定数の数が足りません"
		);
	}
	Poly1d tmp = *this;
	for (int i = 0; i < m; ++i) {
		tmp = tmp.integOnce_(k[i]);
	}
	return tmp;
}

Poly1d Poly1d::derivOnce_() const {
	std::vector<double> deriv_coeffs;
	if (order_ >= 1) {
		for (int n = order_; n >= 1; --n) {
			deriv_coeffs.push_back((*this)[n] * n);
		}
	}
	else {
		deriv_coeffs.push_back(0);
	}

	return Poly1d(deriv_coeffs);
}

Poly1d Poly1d::integOnce_(double k) const {
	std::vector<double> integ_coeffs;
	for (int n = order_; n >= 0; --n) {
		integ_coeffs.push_back((*this)[n] / (n + 1));
	}
	integ_coeffs.push_back(k);

	return Poly1d(integ_coeffs);
}
