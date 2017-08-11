#include "Poly1d.h"
#include <cmath>
#include <cstdio>

const double epsilon = 1e-5;

template <typename T>
bool is_zero(T val) {
	return std::fabs(val) < epsilon;
}

Poly1d::Poly1d(const std::vector<double>& coeffs) {
	if (coeffs.size() > 0) {
		coeffs_ = coeffs;
		order_ = getOrder_();
	}
	else {
		coeffs_.push_back(0);
		order_ = 0;
	}
	size_ = coeffs_.size();
}

std::vector<double> Poly1d::coeffs() const {
	return coeffs_;
}

int Poly1d::order() const {
	return order_;
}

int Poly1d::getOrder_() const {
	/* 高次の項から順番にチェック */
	for (int i = 0; i < size_; ++i) {
		if (is_zero(coeffs_[i])) {
			/* 係数 0 の項は無視する */
		}
		else {
			return size_ - 1 - i;
		}
	}
	/* coeffs_ が空のときは 0 を返す */
	return 0;
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
	for (int i = 0; i < obj.size_; i++) {

	}
}