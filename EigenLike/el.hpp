#ifndef __EL_HPP__
#define __EL_HPP__

#include <stdexcept>
#include <iostream>

/**
 * @namespace el
 * @brief     data stored namespace
 */
namespace el {
	/**
	 * @struct matrix
	 * @brief  matrix
	 */
	template<typename T, int Rows, int Cols>
	struct matrix {
	protected:
		int _rows;  /**< matrix rows */
		int _cols;  /**< matrix cols */
		T **_data;  /**< stored matrix data */

	public:
		/**
		 * @brief  constructor
		 */
		matrix() : _rows(Rows), _cols(Cols) {
			_data = new T*[_rows];
			for (int i = 0; i < _rows; ++i) {
				_data[i] = new T[_cols];
				for (int j = 0; j < _cols; ++j)
					_data[i][j] = T(0);
			}
		}
		/**
		 * @brief  destructor
		 */
		~matrix() {}

		/**
		 * @struct initializer
		 */
		struct initializer {
			matrix<T, Rows, Cols>& m;
			int i;
			initializer(matrix<T, Rows, Cols>& _m, int _i) : m(_m), i(_i) {
				if (i > Rows*Cols) throw std::logic_error("too much arguments");
			}
			initializer operator,(const T x) {
				m._data[i/m.cols()][i%m.rows()] = x;
				return initializer(m, i + 1);
			}
		};
		/**
		 * @fn        initializer operator<<(T x)
		 * @param[in] x element number
		 * @return    element
		 */
		initializer operator<<(const T x) {
			_data[0][0] = x;
			return initializer(*this, 1);
		}

		/**
		 * @fn     T& operator()(int x, int y)
		 * @return matrix(x,y)
		 */
		T& operator()(const int x, const int y) { return _data[x][y]; }

		/**
		 * @fn     const T operator()(int x, int y) const
		 * @return matrix(x,y)
		 */
		const T operator()(const int x, const int y) const { return _data[x][y]; }

		/**
		 * @fn     T* operator[](int idx)
		 * @return matrix[idx]
		 */
		T* operator[](int idx) const { return _data[idx]; }

		/**
		 * @brief  output stream
		 */
		friend std::ostream& operator<<(std::ostream& os, const matrix m) {
			os << "[";
			for (int i = 0; i < m.cols(); ++i) {
				if (i != 0)
					os << " ";
				os << "[";
				for (int j = 0; j < m.rows(); ++j) {
					if (j != 0)
						os << " ";
					os << m[j][i];
					if (j != m.rows() - 1)
						os << ", ";
				}
				os << "]";
				if (i != m.cols() - 1)
					os << "," << std::endl;
			}
			os << "]" << std::endl;
			return os;
		}

		/**
		 * @fn     friend matrix operator+(const matrix& m1, const matrix& m2)
		 * @param[in] m1 left matrix
		 * @param[in] m2 right matrix
		 * @return sum of two matrices
		 */
		friend matrix operator+(const matrix& m1, const matrix& m2) {
			if (m1.rows() != m2.rows() && m1.cols() != m2.cols())
				throw std::logic_error("Not same size");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.cols(); ++i)
				for (int j = 0; j < m1.rows(); ++j)
					r[i][j] = T(m1[i][j]) + T(m2[i][j]);
			return r;
		}

		/**
		 * @fn     inline matrix& operator+=(const matrix& m)
		 * @param[in] m right matrix
		 * @return sum of two matrices
		 */
		inline matrix& operator+=(const matrix& m) {
			if (_rows != m.rows() && _cols != m.cols())
				throw std::logic_error("Not same size");
			for (int i = 0; i < _cols; ++i)
				for (int j = 0; j < _rows; ++j)
					_data[i][j] += T(m[i][j]);
			return *this;
		}

		/**
		 * @fn     friend matrix operator-(const matrix& m1, const matrix& m2)
		 * @param[in] m1 left matrix
		 * @param[in] m2 right matrix
		 * @return diff of two matrices
		 */
		friend matrix operator-(const matrix& m1, const matrix& m2) {
			if (m1.rows() != m2.rows() && m1.cols() != m2.cols())
				throw std::logic_error("Not same size");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.cols(); ++i)
				for (int j = 0; j < m1.rows(); ++j)
					r[i][j] = T(m1[i][j]) - T(m2[i][j]);
			return r;
		}

		/**
		 * @fn     inline matrix& operator-=(const matrix& m)
		 * @param[in] m right matrix
		 * @return diff of two matrices
		 */
		inline matrix& operator-=(const matrix& m) {
			if (_rows != m.rows() && _cols != m.cols())
				throw std::logic_error("Not same size");
			for (int i = 0; i < _cols; ++i)
				for (int j = 0; j < _rows; ++j)
					_data[i][j] -= T(m[i][j]);
			return *this;
		}

		/**
		 * @fn     friend matrix operator*(const T& n, const matrix& m)
		 * @param[in] n left variable
		 * @param[in] m right matrix
		 * @return mul of number and matrix
		 */
		 friend matrix operator*(const T& n, const matrix& m) {
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m.cols(); ++i)
				for (int j = 0; j < m.rows(); ++j)
					r[i][j] = n * T(m[i][j]);
			return r;
		}

		/**
		 * @fn     friend matrix operator*(const matrix& m, const T& n)
		 * @param[in] m left matrix
		 * @param[in] n right variable
		 * @return mul of number and matrix
		 */
		 friend matrix operator*(const matrix& m, const T& n) {
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m.cols(); ++i)
				for (int j = 0; j < m.rows(); ++j)
					r[i][j] = n * T(m[i][j]);
			return r;
		}

		/**
		 * @fn     inline matrix& operator*=(const T& n)
		 * @param[in] n right variable
		 * @return mul of number and matrix
		 */
		inline matrix& operator*=(const T& n) {
			for (int i = 0; i < _cols; ++i)
				for (int j = 0; j < _rows; ++j)
					_data[i][j] *= n;
			return *this;
		}

		/**
		 * @fn     friend matrix operator*(const matrix& m1, const matrix& m2)
		 * @param[in] m1 left matrix
		 * @param[in] m2 right matrix
		 * @return mul of two matrices
		 */
		friend matrix operator*(const matrix& m1, const matrix& m2) {
			if (m1.cols() != m2.rows())
				throw std::logic_error("Left matrix rows is not same Right matrix cols");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.rows(); ++i)
				for (int j = 0; j < m2.cols(); ++j)
					for (int k = 0; k < m1.cols(); ++k)
						r[i][j] += T(m1[i][k]) * T(m2[k][j]);
			return r;
		}

		/**
		 * @fn     inline matrix& operator*=(const matrix& m)
		 * @param[in] m right matrix
		 * @return mul of two matrices
		 */
		inline matrix& operator*=(const matrix& m) {
			if (_cols != m.rows())
				throw std::logic_error("Left matrix rows is not same Right matrix cols");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < _rows; ++i)
				for (int j = 0; j < m.cols(); ++j)
					for (int k = 0; k < _cols; ++k)
						r[i][j] += _data[i][k] * T(m[k][j]);
			*this = r;
			return *this;
		}

		/**
		 * @fn     friend matrix operator*=(const matrix& m1, const matrix& m2)
		 * @param[in] m1 left matrix
		 * @param[in] m2 right matrix
		 * @return mul of two matrices
		 */
		friend matrix operator*=(const matrix& m1, const matrix& m2) {
			if (m1.cols() != m2.rows())
				throw std::logic_error("Left matrix rows is not same Right matrix cols");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.rows(); ++i)
				for (int j = 0; j < m2.cols(); ++j)
					for (int k = 0; k <  m1.cols(); ++k)
						r[i][j] += T(m1[i][k]) * T(m2[k][j]);
			return r;
		}

		/**
		 * @fn     friend matrix operator.(const matrix& m1, const matrix& m2)
		 * @param[in] m left matrix
		 * @param[in] n right variable
		 * @return div of matrix and number
		 */
		friend matrix operator/(const matrix& m, const T& n) {
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m.cols(); ++i)
				for (int j = 0; j < m.rows(); ++j)
					r[i][j] = T(m[i][j]) / n;
			return r;
		}

		/**
		 * @fn     inline matrix& operator/=(const T& n)
		 * @param[in] n right variable
		 * @return div of number and matrix
		 */
		inline matrix& operator/=(const T& n) {
			for (int i = 0; i < _cols; ++i)
				for (int j = 0; j < _rows; ++j)
					_data[i][j] /= n;
			return *this;
		}

		/**
		 * @fn     void zero()
		 * @brief  zero matrix
		 */
		static matrix<T, Rows, Cols> zero() {
			matrix<T, Rows, Cols> m;
			for (int i = 0; i < Cols; ++i)
				for (int j = 0; j < Rows; ++j)
					m[i][j] = T(0);
			return m;
		}
		/**
		 * @fn     void identity()
		 * @brief  identity matrix
		 */
		static matrix<T, Rows, Cols> identity(T n = 1) noexcept {
			if (Rows != Cols) throw std::logic_error("Not square matrix");
			matrix<T, Rows, Cols> m;
			m = matrix<T, Rows, Cols>::zero();
			for (int i = 0; i < Cols; ++i)
				m[i][i] = n;
			return m;
		}
		/**
		 * @fn     void exchange()
		 * @brief  exchange matrix
		 */
		static matrix<T, Rows, Cols> exchange(T n = 1) {
			if (Rows != Cols) throw std::logic_error("Not square matrix");
			matrix<T, Rows, Cols> m;
			m = matrix<T, Rows, Cols>::zero();
			for (int i = 0; i < Cols; ++i)
				m[i][Rows-i-1] = n;
			return m;
		}
		/**
		 * @fn     void ones()
		 * @brief  matrix of ones
		 */
		static matrix<T, Rows, Cols> ones(T n = 1) {
			matrix<T, Rows, Cols> m;
			for (int i = 0; i < Cols; ++i)
				for (int j = 0; j < Rows; ++j)
					m[i][j] = n;
			return m;
		}
		/**
		 * @fn     void hilbelt()
		 * @brief  hilbelt matrix
		 */
		static matrix<T, Rows, Cols> hilbelt(T n = 1) {
			if (Rows != Cols) throw std::logic_error("Not square matrix");
			matrix<T, Rows, Cols> m;
			for (int i = 0; i < Cols; ++i)
				for (int j = 0; j < Rows; ++j)
					m[i][j] = n / (T(i) + T(j) + T(1));
			return m;
		}
		/**
		 * @fn     void lehmer()
		 * @brief  lehmer matrix
		 */
		static matrix<T, Rows, Cols> lehmer() {
			if (Rows != Cols) throw std::logic_error("Not square matrix");
			matrix<T, Rows, Cols> m;
			for (int i = 0; i < Cols; ++i)
				for (int j = 0; j < Rows; ++j){
					if (j >= i){
						m[i][j] = (T(i) + T(1)) / (T(j) + T(1));
					}else{
						m[i][j] = (T(j) + T(1)) / (T(i) + T(1));
					}
				}
			return m;
		}

		/**
		 * @fn     int size()
		 * @return matrix size
		 */
		const int size() const { return _rows * _cols; }
		/**
		 * @fn     int rows()
		 * @return number of matrix rows
		 */
		const int rows() const { return _rows; }
		/**
		 * @fn     int cols()
		 * @return number of matrix cols
		 */
		const int cols() const { return _cols; }
	};

	/**
	 * @struct vector
	 * @brief  vector
	 */
	template<typename T, int Size>
	struct vector : public matrix<T, 1, Size> {
		/**
		 * @fn     T& x()
		 * @return x
		 */
		T& x() noexcept { return this->_data[0][0]; }
		/**
		 * @fn     const T x() const
		 * @return x
		 */
		const T x() const noexcept { return this->_data[0][0]; }
		/**
		 * @fn     T& y()
		 * @return y
		 */
		T& y() noexcept { return this->_data[1][0]; }
		/**
		 * @fn     const T y() const
		 * @return y
		 */
		const T y() const noexcept { return this->_data[1][0]; }
		/**
		 * @fn     T& z()
		 * @return z
		 */
		T& z() noexcept { return this->_data[2][0]; }
		/**
		 * @fn     const T z() const
		 * @return z
		 */
		const T z() const noexcept { return this->_data[2][0]; }
		/**
		 * @fn     T& w()
		 * @return w
		 */
		T& w() noexcept { return this->_data[3][0]; }
		/**
		 * @fn     const T w() const
		 * @return w
		 */
		const T w() const noexcept { return this->_data[3][0]; }
	};


	/**
	 * @struct K
	 * @brief  intrinsic matrix
	 */
	template<typename T>
	struct K : public matrix<T, 3, 3> {
	public:
		/**
		 * @brief  constructor
		 */
		K() {
			this->_data = new T*[this->_cols];
			for (int i = 0; i < this->_cols; ++i) {
				this->_data[i] = new T[this->_rows];
				for (int j = 0; j < this->_rows; ++j)
					this->_data[i][j] = T(0);
			}
			for (int i = 0; i < this->_cols; ++i)
				this->_data[i][i] = T(1);
		}

		/**
		 * @fn        T& fx()
		 * @return    focal length of x axis
		 */
		T& fx() { return this->_data[0][0]; }
		/**
		 * @fn        const T fx() const
		 * @return    focal length of x axis
		 */
		const T fx() const { return this->_data[0][0]; }
		/**
		 * @fn        T& fx()
		 * @return    focal length of y axis
		 */
		T& fy() { return this->_data[1][1]; }
		/**
		 * @fn        const T fy() const
		 * @return    focal length of y axis
		 */
		const T fy() const { return this->_data[1][1]; }
		/**
		 * @fn        T& ppx()
		 * @return    principal point of x axis
		 */
		T& ppx() { return this->_data[0][2]; }
		/**
		 * @fn        const T ppx() const
		 * @return    principal point of x axis
		 */
		const T ppx() const { return this->_data[0][2]; }
		/**
		 * @fn        T& ppy()
		 * @return    principal point of y axis
		 */
		T& ppy() { return this->_data[1][2]; }
		/**
		 * @fn        const T ppy() const
		 * @return    principal point of y axis
		 */
		const T ppy() const { return this->_data[1][2]; }
	};
}

#endif // __EL_HPP__
