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
public: /* �R���X�g���N�^ */
	/**
	  @brief �x�N�^�[��n���Ď��̉�����R���X�g���N�^�B

	  @param [in] vec r = False �̂Ƃ��͑������W������������i�[�����x�N�^�[�Br = True �̂Ƃ��͎��������i�[�����x�N�^�[�B
	  @param [in] r vec ���W���ł��邩(False)�A�������ł��邩(True)
	  @param [in] variable Poly1d �I�u�W�F�N�g���o�̓X�g���[���֕\������Ƃ��Ɏg����ϐ��̕����B
	*/
	Poly1d(const std::vector<double>& vec, bool r = false, const char* variable = "x");

	/**
	  @brief ��̐��l��n���Ď��̉�����R���X�g���N�^�B

	  @param [in] val r = False �̂Ƃ��͒萔���Br = True �̂Ƃ��͎������B
	  @param [in] r val ���萔���ł��邩(False)�A�������ł��邩(True)
	  @param [in] variable Poly1d �I�u�W�F�N�g���o�̓X�g���[���֕\������Ƃ��Ɏg����ϐ��̕����B
	*/
	Poly1d(double val, bool r = false, const char* variable = "x");

public: /* �v�Z�p���\�b�h */
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
	  @brief �������� m ���������

	  @param [in] m ������ (>= 0)
	  @return �����������ʂ� Poly1d �I�u�W�F�N�g�B
	  @exception invalid_argument ���� m ���n���ꂽ�ꍇ�� throw
	*/
	Poly1d deriv(int m = 1) const;

	/**
	  @brief �������� m ��s��ϕ�����

	  @param [in] m �s��ϕ��� (>= 0)
	  @param [in] k �ϕ��萔�Bm ��̂��ׂĂ̐ϕ��œ���̐ϕ��萔��p����B
	  @return �ϕ��������ʂ� Poly1d �I�u�W�F�N�g�B
	  @exception invalid_argument ���� m ���n���ꂽ�ꍇ�� throw
	*/
	Poly1d integ(int m, double k = 0) const;

	/**
	  @brief �������� m ��s��ϕ�����

	  @param [in] m �s��ϕ��� (>= 0)
	  @param [in] k �ϕ��萔�Bm ��̂��ׂĂ̐ϕ��̐ϕ��萔�𖾎��I�Ɏw�肷��B
	  @return �ϕ��������ʂ� Poly1d �I�u�W�F�N�g�B
	  @exception invalid_argument ���� m ���n���ꂽ�ꍇ�� throw
	  @exception invalid_argument �s��ϕ��񐔂ɑ΂��ϕ��萔�̌����s������ꍇ�� throws
	*/
	Poly1d integ(int m, std::vector<double> k) const;

	/**
	  @brief �^����ꂽ���W����ł��߂��������֐���̍��W�����߂�

	  @param [in] p ���W
	  @param [out] nearest point ����ł��߂��������֐���̍��W
	  @return point �� nearest �̋���
	*/
	double nearestPoint(const cv::Point2d& p, cv::Point2d& nearest) const;

public:	/* ���Z�q�I�[�o�[���[�h */
	/**
	@brief ��������㐔�I�ɕ\������

	@param [in, out] ost �o�̓X�g���[��
	@param [in] obj �o�͂������� Poly1d �I�u�W�F�N�g
	@return obj �̓��e����͂������ ost �ւ̎Q��
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);

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
	@brief �������̉��Z���s��

	@param [in] rop
	@return ���Z�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	Poly1d operator+(const Poly1d& rop) const;

	/**
	@brief �萔�ɑ����������Z����

	�萔���E���瑫���ꍇ�͒萔���g���R���X�g���N�^���Ă΂�ĈÖقɃL���X�g�����̂Ŗ��Ȃ��B���̃I�[�o�[���[�h�͒萔�������瑫���ꍇ�B

	@param [in] lop
	@param [in] rop
	@return �萔�����Z�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	friend Poly1d operator+(double lop, const Poly1d& rop);

	/**
	@brief �������̌��Z���s��

	@param [in] rop
	@return ���Z�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	Poly1d operator-(const Poly1d& rop) const;

	/**
	@brief �萔���瑽���������Z����

	�萔�𑽍�����������ꍇ�͒萔���g���R���X�g���N�^���Ă΂�ĈÖقɃL���X�g�����̂Ŗ��Ȃ��B���̃I�[�o�[���[�h�͒萔���瑽�����������ꍇ�B

	@param [in] lop
	@param [in] rop
	@return �萔���猸�Z�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	friend Poly1d operator-(double lop, const Poly1d& rop);

	/**
	@brief �������̕����𔽓]������

	@return �W���̕����𔽓]������ Poly1d �I�u�W�F�N�g
	*/
	Poly1d operator-() const;

	/**
	@brief �������̏�Z

	@param [in] rop
	@return ����������Z�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	Poly1d operator*(const Poly1d& rop) const;

	/**
	@brief �������̏��Z

	�[���R�[�h�͂��� 
	https://en.wikipedia.org/wiki/Polynomial_long_division

	@param [in] rop
	@return ���Z���ʂ� vector�B[0] �� [1] ��]
	*/
	std::vector<Poly1d> operator/(const Poly1d& rop) const;

	/**
	@brief �������̌W�����X�J���[�Ŋ���

	@param [in] rop
	@return ���Z���ʂ� Poly1d �I�u�W�F�N�g
	@exception invalid_argument rop �� 0 �̂Ƃ��� throw
	*/
	Poly1d operator/(double rop) const;


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

	/**
	  @brief �P����������s����B

	  @return �P����������s�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	Poly1d derivOnce_() const;

	/**
	  @brief �P��s��ϕ������s����B

	  @param [in] k �ϕ��萔
	  @return �P��s��ϕ������s�������ʂ� Poly1d �I�u�W�F�N�g
	*/
	Poly1d integOnce_(double k = 0) const;

	/**
	  @brief �������̍ō����̍��̏��Z���ʂ�Ԃ�

	  @param [in] lop Left operand
	  @param [in] rop Right operand
	  @return lop �� rop �̍ō����̍��̏��Z���� Poly1d �I�u�W�F�N�g
	*/
	friend Poly1d divideLeadingTerms_(const Poly1d& lop, const Poly1d& rop);

	/**
	  @brief �������� 0 �ł��邩�ǂ����Ԃ�

	  @return true / false
	*/
	bool is_zero_() const;


};



# endif // POLY1D_H_