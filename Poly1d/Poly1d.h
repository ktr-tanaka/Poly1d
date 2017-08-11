# ifndef POLY1D_H_
# define POLY1D_H_

#include <vector>
#include <ostream>

/**
  @brief �P�ϐ��������������N���X

  numpy.poly1d �Ɠ��l�B
*/
class Poly1d {
public:
	/**
	  @brief �������̌W����n���Ď��̉�����R���X�g���N�^�B

	  @param [in] coeffs �������̌W���B�������珇�Ɋi�[�B
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
	  @brief ��������㐔�I�ɕ\������
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);


private:
	std::vector<double> coeffs_; //!< �������̌W���B�������珇�Ɋi�[�B
	int size_; //!< �������̌W�����i�[���� coeffs_ �̗v�f���B
	int order_; //!< �������̎����B�l 0 �̍��͖�������B

private:
	/**
	  @brief �������̎��������߂ĕԂ��B

	  @return �������̎����B�W�� 0 �̍��͖����B
	*/
	int getOrder_() const;
	/**
	  @brief �������̒l��]�����ĕԂ��B

	  @param [in] x y = f(x) �� x
	  @return y = f(x) �� y
	*/
	double evalPolynomial_(double x) const;
};



# endif // POLY1D_H_