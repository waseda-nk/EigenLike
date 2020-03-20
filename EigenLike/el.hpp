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
			}
			zero();
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
			initializer operator,(T x) {
				m._data[i/m.rows()][i%m.cols()] = x;
				return initializer(m, i + 1);
			}
		};
		initializer operator<<(T x) {
			_data[0][0] = x;
			return initializer(*this, 1);
		}

		T& operator()(int x, int y) { return _data[x][y]; }
		const T operator()(int x, int y) const { return _data[x][y]; }
		T* operator[](int idx) { return _data[idx]; }

		/**
		 * @brief  output stream
		 */
		friend std::ostream& operator<<(std::ostream& os, matrix<T, Rows, Cols>& m) {
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
		 * @fn     void zero()
		 * @brief  zero matrix
		 */
		void zero() {
			for (int i = 0; i < _rows; ++i)
				for (int j = 0; j< _cols; ++j)
					_data[i][j] = 0;
		}
		/**
		 * @fn     void identity()
		 * @brief  identity matrix
		 */
		void identity() {
			if (_rows != _cols) throw("Out of range");
			this->zero();
			for (int i = 0; i < _cols; ++i)
				_data[i][i] = 1;
		}

		/**
		 * @fn     int size()
		 * @return matrix size
		 */
		int size() { return _rows * _cols; }
		/**
		 * @fn     int rows()
		 * @return number of matrix rows
		 */
		int rows() { return _rows; }
		/**
		 * @fn     int cols()
		 * @return number of matrix cols
		 */
		int cols() { return _cols; }
	};

	/**
	 * @struct K
	 * @brief  intrinsic matrix
	 */
	template<typename T>
	struct K : public matrix<T, 3, 3> {
	public:
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