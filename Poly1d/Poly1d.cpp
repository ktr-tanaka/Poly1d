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
static void invert_sign_of_vector(std::vector<T>& vec) {
	for (size_t i = 0, size = vec.size(); i < size; ++i) {
		vec[i] = -vec[i];
	}
}

template <typename T>
static std::vector<T> add_vector(const std::vector<T>& lop, const std::vector<T>& rop) {
	if (lop.size() != rop.size()) {
		throw std::invalid_argument("add_vector: ２つの vector のサイズが異なります");
	}
	size_t size = lop.size();
	std::vector<T> result(size);
	for (size_t i = 0; i < size; ++i) {
		result[i] = lop[i] + rop[i];
	}
	return result;
}

template <typename T>
static std::vector<T> sub_vector(const std::vector<T>& lop, const std::vector<T>& rop) {
	if (lop.size() != rop.size()) {
		throw std::invalid_argument("sub_vector: ２つの vector のサイズが異なります");
	}
	size_t size = lop.size();
	std::vector<T> result(size);
	for (size_t i = 0; i < size; ++i) {
		result[i] = lop[i] - rop[i];
	}
	return result;
}

template <typename T>
static void insert_zero_into_vector(std::vector<T>& vec, int n) {
	for (int i = 0; i < n; ++i) {
		vec.insert(vec.begin(), 0);
	}
}

template <typename T>
static void align_size_of_vectors(std::vector<T>& vec1, std::vector<T>& vec2) {
	/* 要素数が少ないベクターの先頭を 0 で埋める */
	if (vec1.size() > vec2.size()) {
		insert_zero_into_vector(vec2, vec1.size() - vec2.size());
	}
	else if (vec1.size() < vec2.size()) {
		insert_zero_into_vector(vec1, vec2.size() - vec1.size());
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

Poly1d::Poly1d(double val) {
	coeffs_.push_back(val);
	order_ = 0;
	size_ = 1;
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
					ost << std::fabs(obj[n]);
				}
				else {
					ost << obj[n];
				}

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

Poly1d Poly1d::operator-() const {
	std::vector<double> coeffs = this->coeffs_;
	invert_sign_of_vector(coeffs);
	return Poly1d(coeffs);
}

Poly1d Poly1d::operator+(const Poly1d& rop) const {
	std::vector<double> lop_coeffs = this->coeffs_;
	std::vector<double> rop_coeffs = rop.coeffs_;

	align_size_of_vectors(lop_coeffs, rop_coeffs);

	std::vector<double> result_coeffs = add_vector(lop_coeffs, rop_coeffs);

	return Poly1d(result_coeffs);
}

Poly1d operator+(double lop, const Poly1d& rop) {
	Poly1d lop_poly1d(lop);
	return lop_poly1d + rop;
}

Poly1d Poly1d::operator-(const Poly1d& rop) const {
	std::vector<double> lop_coeffs = this->coeffs_;
	std::vector<double> rop_coeffs = rop.coeffs_;

	align_size_of_vectors(lop_coeffs, rop_coeffs);

	std::vector<double> result_coeffs = sub_vector(lop_coeffs, rop_coeffs);

	return Poly1d(result_coeffs);
}

Poly1d operator-(double lop, const Poly1d& rop) {
	Poly1d lop_poly1d(lop);
	return lop_poly1d - rop;
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
