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
public: /* コンストラクタ */
	/**
	  @brief ベクターを渡して実体化するコンストラクタ。

	  @param [in] vec r = False のときは多項式係数を高次から格納したベクター。r = True のときは実数根を格納したベクター。
	  @param [in] r vec が係数であるか(False)、実数根であるか(True)
	  @param [in] variable Poly1d オブジェクトを出力ストリームへ表示するときに使われる変数の文字。
	*/
	Poly1d(const std::vector<double>& vec, bool r = false, const char* variable = "x");

	/**
	  @brief 一つの数値を渡して実体化するコンストラクタ。

	  @param [in] val r = False のときは定数項。r = True のときは実数根。
	  @param [in] r val が定数項であるか(False)、実数根であるか(True)
	  @param [in] variable Poly1d オブジェクトを出力ストリームへ表示するときに使われる変数の文字。
	*/
	Poly1d(double val, bool r = false, const char* variable = "x");

public: /* 計算用メソッド */
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
	  @brief 多項式を m 回微分する

	  @param [in] m 微分回数 (>= 0)
	  @return 微分した結果の Poly1d オブジェクト。
	  @exception invalid_argument 負の m が渡された場合に throw
	*/
	Poly1d deriv(int m = 1) const;

	/**
	  @brief 多項式を m 回不定積分する

	  @param [in] m 不定積分回数 (>= 0)
	  @param [in] k 積分定数。m 回のすべての積分で同一の積分定数を用いる。
	  @return 積分した結果の Poly1d オブジェクト。
	  @exception invalid_argument 負の m が渡された場合に throw
	*/
	Poly1d integ(int m, double k = 0) const;

	/**
	  @brief 多項式を m 回不定積分する

	  @param [in] m 不定積分回数 (>= 0)
	  @param [in] k 積分定数。m 回のすべての積分の積分定数を明示的に指定する。
	  @return 積分した結果の Poly1d オブジェクト。
	  @exception invalid_argument 負の m が渡された場合に throw
	  @exception invalid_argument 不定積分回数に対し積分定数の個数が不足する場合に throws
	*/
	Poly1d integ(int m, std::vector<double> k) const;

	/**
	  @brief 与えられた座標から最も近い多項式関数上の座標を求める

	  @param [in] p 座標
	  @param [out] nearest point から最も近い多項式関数上の座標
	  @return point と nearest の距離
	*/
	double nearestPoint(const cv::Point2d& p, cv::Point2d& nearest) const;

public:	/* 演算子オーバーロード */
	/**
	@brief 多項式を代数的に表示する

	@param [in, out] ost 出力ストリーム
	@param [in] obj 出力させたい Poly1d オブジェクト
	@return obj の内容を入力した後の ost への参照
	*/
	friend std::ostream& operator<<(std::ostream& ost, const Poly1d& obj);

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
	@brief 多項式の加算を行う

	@param [in] rop
	@return 加算した結果の Poly1d オブジェクト
	*/
	Poly1d operator+(const Poly1d& rop) const;

	/**
	@brief 定数に多項式を加算する

	定数を右から足す場合は定数を使うコンストラクタが呼ばれて暗黙にキャストされるので問題なし。このオーバーロードは定数を左から足す場合。

	@param [in] lop
	@param [in] rop
	@return 定数を加算した結果の Poly1d オブジェクト
	*/
	friend Poly1d operator+(double lop, const Poly1d& rop);

	/**
	@brief 多項式の減算を行う

	@param [in] rop
	@return 減算した結果の Poly1d オブジェクト
	*/
	Poly1d operator-(const Poly1d& rop) const;

	/**
	@brief 定数から多項式を減算する

	定数を多項式から引く場合は定数を使うコンストラクタが呼ばれて暗黙にキャストされるので問題なし。このオーバーロードは定数から多項式を引く場合。

	@param [in] lop
	@param [in] rop
	@return 定数から減算した結果の Poly1d オブジェクト
	*/
	friend Poly1d operator-(double lop, const Poly1d& rop);

	/**
	@brief 多項式の符号を反転させる

	@return 係数の符号を反転させた Poly1d オブジェクト
	*/
	Poly1d operator-() const;

	/**
	@brief 多項式の乗算

	@param [in] rop
	@return 多項式を乗算した結果の Poly1d オブジェクト
	*/
	Poly1d operator*(const Poly1d& rop) const;

	/**
	@brief 多項式の除算

	擬似コードはここ 
	https://en.wikipedia.org/wiki/Polynomial_long_division

	@param [in] rop
	@return 除算結果の vector。[0] 商 [1] 剰余
	*/
	std::vector<Poly1d> operator/(const Poly1d& rop) const;

	/**
	@brief 多項式の係数をスカラーで割る

	@param [in] rop
	@return 除算結果の Poly1d オブジェクト
	@exception invalid_argument rop が 0 のときに throw
	*/
	Poly1d operator/(double rop) const;


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

	/**
	  @brief １回微分を実行する。

	  @return １回微分を実行した結果の Poly1d オブジェクト
	*/
	Poly1d derivOnce_() const;

	/**
	  @brief １回不定積分を実行する。

	  @param [in] k 積分定数
	  @return １回不定積分を実行した結果の Poly1d オブジェクト
	*/
	Poly1d integOnce_(double k = 0) const;

	/**
	  @brief 多項式の最高次の項の除算結果を返す

	  @param [in] lop Left operand
	  @param [in] rop Right operand
	  @return lop と rop の最高次の項の除算結果 Poly1d オブジェクト
	*/
	friend Poly1d divideLeadingTerms_(const Poly1d& lop, const Poly1d& rop);

	/**
	  @brief 多項式が 0 であるかどうか返す

	  @return true / false
	*/
	bool is_zero_() const;


};



# endif // POLY1D_H_