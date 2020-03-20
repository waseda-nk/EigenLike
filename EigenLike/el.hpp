#ifndef __EL_HPP__
#define __EL_HPP__

#include <iostream>

/**
 * @namespace el
 * @brief     data stored namespace
 */
namespace el {

	/**
	 * @struct vector
	 * @brief  vector
	 */
	template<typename T, int Size>
	struct vector {
		/**
		 * @brief  constructor
		 */
		vector() : _size(Size) {
			_data = new T[_size];
			for (int i = 0; i < _size; ++i)
				_data[i] = (T)0;
		}
		/**
		 * @brief  destructor
		 */
		~vector() {}

		/**
		 * @struct initializer  
		 */
		struct initializer {
			vector<T, Size>& v;
			int i;
			initializer(vector<T, Size>& _v, int _i) : v(_v), i(_i) {
				if (i > Size) throw("Out of range");
			}
			initializer operator,(T x) noexcept {
				v._data[i % Size] = x;
				return initializer(v, i + 1);
			}
		};
		/**
		 * @fn        initializer operator<<(T x)
		 * @param[in] x element number
		 * @return    element
		 */
		initializer operator<<(T x) noexcept {
			_data[0] = x;
			return initializer(*this, 1);
		}

		/**
		 * @fn        T& operator()(int idx)
		 * @param[in] idx element number
		 * @return    element
		 */
		T& operator()(int idx) { return _data[idx]; }

		/**
		 * @fn        const T operator()(int idx) const
		 * @param[in] idx element number
		 * @return    element
		 */
		const T operator()(int idx) const { return _data[idx]; }

		/**
		 * @fn        T& operator[](int idx)
		 * @param[in] idx element number
		 * @return    element
		 */
		T& operator[](int idx) { return _data[idx]; }

		/**
		 * @fn        const T operator[](int idx) const
		 * @param[in] idx element number
		 * @return    element
		 */
		const T operator[](int idx) const { return _data[idx]; }

		/**
		 * @fn        friend std::ostream& operator<<(std::ostream& os, vector<T, Size>& v)
		 * @param[in]  os output stream
		 * @param[in]  v  vector
		 * @return    output stream
		 */
		friend std::ostream& operator<<(std::ostream& os, vector<T, Size>& v) {
			os << "[";
			for (int i = 0; i < v.size(); ++i) {
				if (i != 0)
					os << " ";
				os << v[i];
				if (i != v.size() - 1)
					os << ", " << std::endl;
			}
			os << "]" << std::endl;
			return os;
		}

		/**
		 * @fn     int size()
		 * @return vector size
		 */
		int size() { return _size; }

		/**
		 * @fn     T& x()
		 * @return x
		 */
		T& x() noexcept { return _data[0]; }
		/**
		 * @fn     const T x() const
		 * @return x
		 */
		const T x() const noexcept { return _data[0]; }
		/**
		 * @fn     T& y()
		 * @return y
		 */
		T& y() noexcept { return _data[1]; }
		/**
		 * @fn     const T y() const
		 * @return y
		 */
		const T y() const noexcept { return _data[1]; }
		/**
		 * @fn     T& z()
		 * @return z
		 */
		T& z() noexcept { return _data[2]; }
		/**
		 * @fn     const T z() const
		 * @return z
		 */
		const T z() const noexcept { return _data[2]; }
		/**
		 * @fn     T& w()
		 * @return w
		 */
		T& w() noexcept { return _data[3]; }
		/**
		 * @fn     const T w() const
		 * @return w
		 */
		const T w() const noexcept { return _data[3]; }
	protected:
		int _size;  /**< vector size */
		T *_data;   /**< stored vector data */
	};

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
			_data = new T*[_cols];
			for (int i = 0; i < _cols; ++i) {
				_data[i] = new T[_rows];
				for (int j = 0; j < _rows; ++j)
					_data[i][j] = 0;
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
				if (i > Rows*Cols) throw("Out of range");
			}
			initializer operator,(const T x) {
				m._data[i/m.rows()][i%m.cols()] = x;
				return initializer(m, i + 1);
			}
		};
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
			for (int i = 0; i < m.rows(); ++i) {
				if (i != 0)
					os << " ";
				os << "[";
				for (int j = 0; j < m.cols(); ++j) {
					if (j != 0)
						os << " ";
					os << m[i][j];
					if (j != m.cols() - 1)
						os << ", ";
				}
				os << "]";
				if (i != m.rows() - 1)
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
				throw("Not same size");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.rows(); ++i)
				for (int j = 0; j < m1.cols(); ++j)
					r[i][j] = m1[i][j] + m2[i][j];
			return r;
		}

		/**
		 * @fn     friend matrix operator-(const matrix& m1, const matrix& m2)
		 * @param[in] m1 left matrix
		 * @param[in] m2 right matrix
		 * @return diff of two matrices
		 */
		friend matrix operator-(const matrix& m1, const matrix& m2) {
			if (m1.rows() != m2.rows() && m1.cols() != m2.cols())
				throw("Not same size");
			matrix<T, Rows, Cols> r;
			for (int i = 0; i < m1.rows(); ++i)
				for (int j = 0; j < m1.cols(); ++j)
					r[i][j] = m1[i][j] - m2[i][j];
			return r;
		}

		/**
		 * @fn     void zero()
		 * @brief  zero matrix
		 */
		static matrix<T, Rows, Cols> zero() {
			matrix<T, Rows, Cols> m;
			for (int i = 0; i < Rows; ++i)
				for (int j = 0; j < Cols; ++j)
					m[i][j] = 0;
			return m;
		}
		/**
		 * @fn     void identity()
		 * @brief  identity matrix
		 */
		static matrix<T, Rows, Cols> identity(T n = 1) {
			if (Rows != Cols) throw("Out of range");
			matrix<T, Rows, Cols> m;
			m = matrix<T, Rows, Cols>::zero();
			for (int i = 0; i < Cols; ++i)
				m[i][i] = n;
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
					this->_data[i][j] = 0;
			}
			for (int i = 0; i < this->_cols; ++i)
				this->_data[i][i] = 0;
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