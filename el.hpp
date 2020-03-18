#ifndef __EL_HPP__
#define __EL_HPP__

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
			for (size_t i = 0; i < _size; ++i)
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
			vector<T, Size> &v;
			int i;
			initializer(vector<T, Size> _v, int _i) : v(_v), i(_i) {
				if (i > Size) throw("Out of range");
			}
			initializer operator,(T x) {
				v._data[i%Size] = x;
				return initializer(v, i + 1);
			}
		};
		initializer operator<<(T x) {
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
		 * @fn     int size()
		 * @return vector size
		 */
		int size() { return _size; }
	private:
		int _size;  /**< vector size */
		T *_data;           /**< stored vector data */
	};

	/**
	 * @struct matrix
	 * @brief  matrix
	 */
	template<typename T, int Rows, int Cols>
	struct matrix {
		/**
		 * @brief  constructor
		 */
		matrix() : _rows(Rows), _cols(Cols) {
			*_data = new T*[_cols];
			for (size_t i = 0; i < _cols; ++i)
				_data[i] = new T[_rows];
		}
		/**
		 * @brief  destructor
		 */
		~matrix() {}

		/**
		 * @struct initializer
		 */
		struct initializer {
			matrix<T, Rows, Cols> &m;
			int i;
			initializer(matrix<T, Rows, Cols> _m, int _i) : m(_m), i(_i) {
				if (i > Rows*Cols) throw("Out of range");
			}
			initializer operator,(T x) {
				m._data[i/ Rows][i%Cols] = x;
				return initializer(m, i + 1);
			}
		};
		initializer operator<<(T x) {
			_data[0][0] = x;
			return initializer(*this, 1);
		}

		/**
		 * @fn     int size()
		 * @return matrix size
		 */
		int size() { return _rows*_cols; }

	private:
		int _rows;  /**< matrix rows */
		int _cols;  /**< matrix cols */
		T **_data;  /**< stored matrix data */
	};
}


#endif // __EL_HPP__