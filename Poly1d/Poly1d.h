# ifndef POLY1D_H_
# define POLY1D_H_

#include <vector>
#include <ostream>

/**
  @brief １変数多項式を扱うクラス

  numpy.poly1d と同様。
*/
class Poly1d {
public:
	/**
	  @brief 多項式の係数を渡して実体化するコンストラクタ。

	  @param [in] coeffs 多項式の係数。高次から順に格納。
	*/
	Poly1d(const std::vector<double>& coeffs);

public:
	/**
	  @brief 多項式の係数を返す。

	  @return 係数のコピー
	*/
	std::vector<double> coeffs() const;	

	/**
	  @brief 多項式の次数を返す。
	 
	  @return 次数
	*/
	int order() const;

	/**
	  @brief 多項式の値を計算して結果を返す。

	  @param [in] x y = f(x) の x
	  @return y = f(x) の y
	*/
	double operator()(double x) const;

	/**
	  @brief 指定した次数の項の係数を返す。

	  係数を格納したベクターの範囲外が参照された場合は 0 を返す。

	  @param [in] n 次数
	  @return 対応する係数
	*/
	double operator[](int n) const;

	/**
	  @brief 多項式を代数的に表示する
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);


private:
	std::vector<double> coeffs_; //!< 多項式の係数。高次から順に格納。
	int size_; //!< 多項式の係数を格納した coeffs_ の要素数。
	int order_; //!< 多項式の次数。値 0 の項は無視する。

private:
	/**
	  @brief 多項式の次数を求めて返す。

	  @return 多項式の次数。係数 0 の項は無視。
	*/
	int getOrder_() const;
	/**
	  @brief 多項式の値を評価して返す。

	  @param [in] x y = f(x) の x
	  @return y = f(x) の y
	*/
	double evalPolynomial_(double x) const;
};



# endif // POLY1D_H_