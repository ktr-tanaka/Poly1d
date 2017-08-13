#include "Poly1d.h"
#include <cmath>
#include <iomanip>
#include <ostream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

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
		throw std::invalid_argument("add_vector: ‚Q‚Â‚Ì vector ‚ÌƒTƒCƒY‚ªˆÙ‚È‚è‚Ü‚·");
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
		throw std::invalid_argument("sub_vector: ‚Q‚Â‚Ì vector ‚ÌƒTƒCƒY‚ªˆÙ‚È‚è‚Ü‚·");
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
	/* —v‘f”‚ª­‚È‚¢ƒxƒNƒ^[‚Ìæ“ª‚ğ 0 ‚Å–„‚ß‚é */
	if (vec1.size() > vec2.size()) {
		insert_zero_into_vector(vec2, vec1.size() - vec2.size());
	}
	else if (vec1.size() < vec2.size()) {
		insert_zero_into_vector(vec1, vec2.size() - vec1.size());
	}
}

Poly1d::Poly1d(const std::vector<double>& vec, bool r, const char* variable) {
	if (r == false) {
		/* vec ‚Í‘½€®‚ÌŒW” */
		std::vector<double> coeffs = vec;
		variable_ = std::string(variable);
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
	}
	else {
		/* vec ‚Í‘½€®‚ÌÀ”ª */
		std::vector<double> roots = vec;
		Poly1d temp(0);
		if (roots.empty()) {
			/* x ‚Å‰Šú‰» */
			std::vector<double> coeffs = { 1, 0 };
			temp = Poly1d(coeffs);
		}
		else {
			temp = Poly1d(1);
			for each (double root in roots) {
				std::vector<double> x = { 1, 0 };
				temp = temp * (Poly1d(x) - root);
			}
		}
		variable_ = std::string(variable);
		coeffs_ = temp.coeffs_;
		size_ = temp.size_;
		order_ = temp.order_;
	}
}

Poly1d::Poly1d(double val, bool r, const char* variable) {
	if (r == false) {
		/* val ‚Å‰Šú‰» */
		coeffs_.push_back(val);
		order_ = 0;
		size_ = 1;
	}
	else {
		/* x - val ‚Å‰Šú‰» */
		std::vector<double> coeffs = { 1, -val };
		coeffs_ = coeffs;
		order_ = 1;
		size_ = 2;
	}
	variable_ = std::string(variable);
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
	if (obj.order_ == 0) {
		ost << obj[0];
		return ost;
	}
	else {
		for (int n = obj.order_; n >= 0; --n) {
			if (is_zero(obj[n])) {
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

Poly1d Poly1d::operator*(const Poly1d& rop) const {
	std::vector<double> lop_coeffs = this->coeffs_;
	std::vector<double> rop_coeffs = rop.coeffs_;
	int lop_order = this->order_;
	int rop_order = rop.order_;

	/* ‚Ü‚¸ŠÈ’P‚Ì‚½‚ß‚ÉAresult_coeffs‚É‚Í’áŸ‚Ì€‚©‚ç‡”Ô‚É‹l‚ß‚Ä‚¢‚­‚±‚Æ‚É‚·‚é */
	/* result_coeffs ‚Í‚Ü‚¸ 0 ‚Å‘S—v‘f‰Šú‰»‚·‚é */
	std::vector<double> result_coeffs(lop_order + rop_order + 1, 0);
	for (int m = lop_order; m >= 0; --m) {
		for (int n = rop_order; n >= 0; --n) {
			/* m + n Ÿ‚Ì€‚ÌŒW”‚É‘«‚µ‚Ş */
			result_coeffs[m + n] += (*this)[m] * rop[n];
		}
	}
	/* ‚ŸŒW”‚©‚ç‚É•À‚Ñ‘Ö‚¦‚é */
	std::reverse(result_coeffs.begin(), result_coeffs.end());

	return Poly1d(result_coeffs);
}

std::vector<Poly1d> Poly1d::operator/(const Poly1d& denominator) const {
	if (denominator.is_zero_()) {
		throw std::invalid_argument("0 œZ‚Å‚·");
	}
	Poly1d numerator = (*this);

	Poly1d quotient(0);
	Poly1d reminder = (*this);
	while ((!reminder.is_zero_()) && (reminder.order_ >= denominator.order_)) {
		Poly1d temp = divideLeadingTerms_(reminder, denominator);
		quotient = quotient + temp;
		reminder = reminder - temp * denominator;
	}
	std::vector<Poly1d> result = { quotient, reminder };
	return result;
}

Poly1d Poly1d::operator/(double rop) const {
	if (is_zero(rop)) {
		throw std::invalid_argument("0 œZ‚Å‚·");
	}
	return (*this) * (1.0 / rop);
}

bool Poly1d::is_zero_() const {
	if (this->order_ == 0 && is_zero(this->coeffs_[0])) {
		return true;
	}
	else {
		return false;
	}
}

Poly1d divideLeadingTerms_(const Poly1d& lop, const Poly1d& rop) {
	if (lop.order_ < rop.order_) {
		return Poly1d(0);
	}
	else {
		/* Å‚Ÿ‚ÌŒW”‚ÌœZ */
		double coeff = lop.coeffs_[0] / rop.coeffs_[0];
		/* ‚»‚ÌŸ” */
		int order = lop.order_ - rop.order_;
		/* ŒW”‚ÌƒxƒNƒ^[‚ğì»B0 ‚Å‰Šú‰» */
		std::vector<double> coeffs(order + 1, 0);
		coeffs[0] = coeff;
		return Poly1d(coeffs);
	}
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

Poly1d Poly1d::deriv(int m) const {
	if (m < 0) {
		throw std::invalid_argument(
			"”÷•ª‰ñ”‚Í 0 ˆÈã‚Å‚È‚¯‚ê‚Î‚È‚è‚Ü‚¹‚ñ"
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
			"Ï•ª‰ñ”‚Í 0 ˆÈã‚Å‚È‚¯‚ê‚Î‚È‚è‚Ü‚¹‚ñ"
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
			"Ï•ª‰ñ”‚Í 0 ˆÈã‚Å‚È‚¯‚ê‚Î‚È‚è‚Ü‚¹‚ñ"
		);
	}
	if (m > k.size()) {
		/* TODO vector‚Ì—Ìˆæ‚ÍŠm•Û‚³‚ê‚Ä‚¢‚é‚ª’†g‚ª‰Šú‰»‚³‚ê‚Ä‚¢‚È‚¢‚Æ‚«‚Ìsize()‚Ì‹““®‚ÍH */
		throw std::invalid_argument(
			"Ï•ª’è”‚Ì”‚ª‘«‚è‚Ü‚¹‚ñ"
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

double Poly1d::nearestPoint(const cv::Point2d& p, cv::Point2d& nearest) const {
	std::vector<double> t_coeffs = { 1, 0 };
	Poly1d t(t_coeffs);

	Poly1d ll = (p.x - t)*(p.x - t) + (p.y - (*this))*(p.y - (*this));

	Poly1d dll_dt = ll.deriv();
	std::vector<double> dll_dt_roots = dll_dt.rootsReal();

	double ll_min = std::numeric_limits<double>::max();
	double t_min;
	for each (double t_temp in dll_dt_roots) {
		double ll_temp = ll(t_temp);
		if (ll_temp < ll_min) {
			ll_min = ll_temp;
			t_min = t_temp;
		}
	}
	nearest.x = t_min;
	nearest.y = (*this)(t_min);

	return std::sqrt(ll_min);
}

