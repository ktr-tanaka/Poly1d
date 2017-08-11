# ifndef POLY1D_H_
# define POLY1D_H_

#include <opencv2\core.hpp>

#include <vector>
#include <ostream>
#include <string>

/**
  @brief �P�ϐ��������������N���X

  numpy.poly1d �Ɠ��l�B
*/
class Poly1d {
public:
	/**
	  @brief �������̌W����n���Ď��̉�����R���X�g���N�^�B

	  @param [in] coeffs �������̌W���B�������珇�Ɋi�[
	*/
	Poly1d(const std::vector<double>& coeffs);

public:
	/**
	  @brief �������̌W����Ԃ��B

	  @return �W���̃R�s�[
	*/
	std::vector<double> coeffs() const;	

	/**
	  @brief �������̎�����Ԃ��B
	 
	  @return ����
	*/
	int order() const;

	/**
	  @brief �������̒l���v�Z���Č��ʂ�Ԃ��B

	  @param [in] x y = f(x) �� x
	  @return y = f(x) �� y
	*/
	double operator()(double x) const;

	/**
	  @brief �w�肵�������̍��̌W����Ԃ��B

	  �W�����i�[�����x�N�^�[�͈̔͊O���Q�Ƃ��ꂽ�ꍇ�� 0 ��Ԃ��B

	  @param [in] n ����
	  @return �Ή�����W��
	*/
	double operator[](int n) const;

	/**
	  @brief �������̍������߂�B

	  vector �̊e�v�f�� cv::Vec2d(�����A�����j�̌`���B

	  @return ���i�����j
	*/
	std::vector<cv::Vec2d> roots() const;

	/**
	  @brief �������̎����������߂�B

	  @note �����������݂��Ȃ��ꍇ�͋�̃x�N�^�[���Ԃ���܂��B

	  @param [in] epsilon �����̐�Βl�� epsilon �����̏ꍇ�A�����Ɣ��肷��B
	  @return �������B�����������݂��Ȃ��ꍇ�͋�̃x�N�^�[��Ԃ��B
	*/
	std::vector<double> rootsReal(double epsilon = 1e-7) const;

	/**
	  @brief ��������㐔�I�ɕ\������

	  @param [in, out] ost �o�̓X�g���[��
	  @param [in] obj �o�͂������� Poly1d �I�u�W�F�N�g
	  @return obj �̓��e����͂������ ost �ւ̎Q��
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);

	/**
	  @brief ���������������

	  @return �����������ʂ� Poly1d �I�u�W�F�N�g�B
	*/
	Poly1d deriv() const;

	/**
	  @brief ��������ϕ�����

	  @return �ϕ��������ʂ� Poly1d �I�u�W�F�N�g�B
	*/
	Poly1d integ() const;


private:
	std::vector<double> coeffs_; //!< �������̌W���B�������珇�Ɋi�[�B
	int size_; //!< �������̌W�����i�[���� coeffs_ �̗v�f���B
	int order_; //!< �������̎����B�l 0 �̍��͖�������B
	std::string variable_; //!< ���������o�͂���Ƃ��̕ϐ���\������

private:
	/**
	  @brief �������̒l��]�����ĕԂ��B

	  �I�u�W�F�N�g����Ďg�������ꍇ�� operator() ���g�p����B

	  @param [in] x y = f(x) �� x
	  @return y = f(x) �� y
	*/
	double evalPolynomial_(double x) const;

	/**
	  @brief �������̍������߂ĕԂ��B

	  cv::solvePoly ���g�p����B

	  @return ���i���������܂ށj
	*/
	std::vector<cv::Vec2d> getRoots_() const;
};



# endif // POLY1D_H_