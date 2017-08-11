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
	/* �����̍����珇�ԂɃ`�F�b�N */
	for (int i = 0; i < size_; ++i) {
		if (is_zero(coeffs_[i])) {
			/* �W�� 0 �̍��͖������� */
		}
		else {
			return size_ - 1 - i;
		}
	}
	/* coeffs_ ����̂Ƃ��� 0 ��Ԃ� */
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
		/* �͈͊O�̏ꍇ�͂��̎����̍��̌W���� 0 �Ƃ��� */
		return 0;
	}
}

std::ostream& operator<<(std::ostream& ost, const Poly1d& obj) {
	for (int i = 0; i < obj.size_; i++) {

	}
}