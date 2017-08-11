# ifndef POLY1D_H_
# define POLY1D_H_

#include <opencv2\core.hpp>

#include <vector>
#include <ostream>
#include <string>

/**
  @brief １変数多項式を扱うクラス

  numpy.poly1d と同様。
*/
class Poly1d {
public:
	/**
	  @brief 多項式の係数を渡して実体化するコンストラクタ。

	  @param [in] coeffs 多項式の係数。高次から順に格納
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
	  @brief 多項式の根を求める。

	  vector の各要素は cv::Vec2d(実部、虚部）の形式。

	  @return 根（虚数）
	*/
	std::vector<cv::Vec2d> roots() const;

	/**
	  @brief 多項式の実数根を求める。

	  @note 実数根が存在しない場合は空のベクターが返されます。

	  @param [in] epsilon 虚部の絶対値が epsilon 未満の場合、実数と判定する。
	  @return 実数根。実数根が存在しない場合は空のベクターを返す。
	*/
	std::vector<double> rootsReal(double epsilon = 1e-7) const;

	/**
	  @brief 多項式を代数的に表示する

	  @param [in, out] ost 出力ストリーム
	  @param [in] obj 出力させたい Poly1d オブジェクト
	  @return obj の内容を入力した後の ost への参照
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);

	/**
	  @brief 多項式を微分する

	  @return 微分した結果の Poly1d オブジェクト。
	*/
	Poly1d deriv() const;

	/**
	  @brief 多項式を積分する

	  @return 積分した結果の Poly1d オブジェクト。
	*/
	Poly1d integ() const;


private:
	std::vector<double> coeffs_; //!< 多項式の係数。高次から順に格納。
	int size_; //!< 多項式の係数を格納した coeffs_ の要素数。
	int order_; //!< 多項式の次数。値 0 の項は無視する。
	std::string variable_; //!< 多項式を出力するときの変数を表す文字

private:
	/**
	  @brief 多項式の値を評価して返す。

	  オブジェクトを介して使いたい場合は operator() を使用する。

	  @param [in] x y = f(x) の x
	  @return y = f(x) の y
	*/
	double evalPolynomial_(double x) const;

	/**
	  @brief 多項式の根を求めて返す。

	  cv::solvePoly を使用する。

	  @return 根（虚数根も含む）
	*/
	std::vector<cv::Vec2d> getRoots_() const;
};



# endif // POLY1D_H_