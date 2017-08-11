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
		/* ”ÍˆÍŠO‚Ìê‡‚Í‚»‚ÌŸ”‚Ì€‚ÌŒW”‚Í 0 ‚Æ‚·‚é */
		return 0;
	}
}

std::ostream& operator<<(std::ostream& ost, const Poly1d& obj) {
	for (int n = obj.order_; n >= 0; --n) {
		if (is_zero(obj[n])){
			/* ŒW”‚ª 0 ‚È‚ç•\¦‚µ‚È‚¢ */
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
	/* ‹•”ª‚àŠÜ‚ß‚Äª‚ğ‹‚ß‚é */
	std::vector<cv::Vec2d> tmp = getRoots_();
	std::vector<double> real_roots;
	for each (cv::Vec2d root in tmp) {
		/* root[0]: À•”, root[1]: ‹••” */
		if (is_zero(root[1], epsilon)) {
			real_roots.push_back(root[0]);
		}
	}
	return real_roots;
}

std::vector<cv::Vec2d> Poly1d::getRoots_() const {
	/* solvePoly ‚É“n‚·‘½€®ŒW”‚ÍA’áŸ‚©‚ç‡‚ÉŠi”[‚·‚é•K—v‚ª‚ ‚é */
	std::vector<double> tmp = coeffs_;
	std::reverse(tmp.begin(), tmp.end());
	std::vector<cv::Vec2d> result;
	cv::solvePoly(tmp, result);
	return result;
}