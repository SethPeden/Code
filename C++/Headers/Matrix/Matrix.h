#ifndef MATRIX_H
#define MATRIX_H
// Matrix.h
// Seth Peden
// March 13, 2018

#include <iostream>

template <typename T>
class Matrix {
	int rows, columns, *sizes, *offsets;
	T **data;

public:
	Matrix(int rows, int columns) {
		this->rows = rows;
		this->columns = columns;
		if (this->rows) {
			this->sizes = new int[this->rows];
			this->offsets = new int[this->rows];
			this->data = new T *[this->rows];
			for (int r = 0; r < this->rows; r++) {
				this->sizes[r] = this->offsets[r] = 0;
				this->data[r] = nullptr;
			}
		} else {
			this->sizes = this->offsets = nullptr;
			this->data = nullptr;
		}
	}
	Matrix(const Matrix &copy) {
		this->rows = copy.rows;
		this->columns = copy.columns;
		if (this->rows) {
			this->sizes = new int[this->rows];
			this->offsets = new int[this->rows];
			this->data = new T *[this->rows];
			for (int r = 0; r < this->rows; r++) {
				this->sizes[r] = copy.sizes[r];
				this->offsets[r] = copy.offsets[r];
				this->data[r] = new T[this->sizes[r]];
				for (int c = 0; c < this->sizes[r]; c++)
					this->data[r][c] = copy.data[r][c];
			}
		} else {
			this->sizes = this->offsets = nullptr;
			this->data = nullptr;
		}
	}
	~Matrix() {
		for (int r = 0; r < this->rows; r++)
			delete[] this->data[r];
		delete this->sizes;
		delete this->offsets;
	}
	Matrix operator =(const Matrix &copy) {
		for (int r = 0; r < this->rows; r++)
			delete[] this->data[r];
		delete this->sizes;
		delete this->offsets;
		this->rows = copy.rows;
		this->columns = copy.columns;
		if (this->rows) {
			this->sizes = new int[this->rows];
			this->offsets = new int[this->rows];
			this->data = new T *[this->rows];
			for (int r = 0; r < this->rows; r++) {
				this->sizes[r] = copy.sizes[r];
				this->offsets[r] = copy.offsets[r];
				this->data[r] = new T[this->sizes[r]];
				for (int c = 0; c < this->sizes[r]; c++)
					this->data[r][c] = copy.data[r][c];
			}
		} else {
			this->sizes = this->offsets = nullptr;
			this->data = nullptr;
		}
		return *this;
	}
	bool set(int row, int column, T value) {
		if (row >= 0 and row < this->rows and column >= 0 and column < this->columns) {
			if (this->sizes[row]) {
				// Row is non-empty
				if (column < this->offsets[row]) {
					// Prepend
					int newCount = this->offsets[row] - column;
					T *old = this->data[row];
					this->data[row] = new T[this->sizes[row] + newCount];
					this->data[row][0] = value;
					for (int c = 1; c < newCount; c++) 
						this->data[row][c] = T(0);
					for (int c = 0; c < this->sizes[row]; c++)
						this->data[row][newCount + c] = old[c];
					this->sizes[row] += newCount;
					this->offsets[row] = column;
					delete[] old;
				} else if (column - this->offsets[row] > this->sizes[row] - 1) {
					// Append
					int newCount = column - this->offsets[row] - this->sizes[row] + 1;
					T *old = this->data[row];
					this->data[row] = new T[this->sizes[row] + newCount];
					for (int c = 0; c < this->sizes[row]; c++)
						this->data[row][c] = old[c];
					for (int c = this->sizes[row]; c < this->sizes[row] + newCount - 1; c++)
						this->data[row][c] = T(0);
					this->data[row][this->sizes[row] + newCount - 1] = value;
					this->sizes[row] += newCount;
					delete[] old;
				} else {
					// Modify within the array
					this->data[row][column - this->offsets[row]] = value;
				}
				// Trim
				T *untrimmed = this->data[row];
				int removeFront = 0;
				int removeBack = 0;
				while (removeFront < this->sizes[row] and !this->data[row][removeFront])
					removeFront++;
				while (removeBack + removeFront < this->sizes[row] and !this->data[row][this->sizes[row] - removeBack - 1])
					removeBack++;
				this->data[row] = new T[this->sizes[row] - removeFront - removeBack];
				for (int c = removeFront; c < this->sizes[row] - removeBack; c++)
					this->data[row][c - removeFront] = untrimmed[c];
				this->sizes[row] -= removeFront + removeBack;
				this->offsets[row] += removeFront;
				delete[] untrimmed;
				return true;
			} else {
				// Row is empty
				if (value != T(0)) {
					this->sizes[row] = 1;
					this->offsets[row] = column;
					this->data[row] = new T[1];
					this->data[row][0] = value;
				}
				return true;
			}
		}
		return false;
	}
	T get(int row, int column) {
		int index = column - this->offsets[row];
		if (index >= T(0) and index < this->sizes[row])
			return this->data[row][index];
		return T(0);
	}
	Matrix operator +(Matrix matrix) {
		if (this->rows == matrix.rows and this->columns == matrix.columns) {
			Matrix ans(this->rows, this->columns);
			for (int r = 0; r < this->rows; r++)
				for (int c = 0; c < this->columns; c++)
					ans.set(r, c, this->get(r, c) + matrix.get(r, c));
			return ans;
		} else {
			return Matrix(T(0), T(0));
		}
	}
	Matrix operator *(T scalar) {
		Matrix ans(this->rows, this->columns);
		for (int r = 0; r < this->rows; r++)
			for (int c = 0; c < this->columns; c++)
				ans.set(r, c, scalar * this->get(r, c));
		return ans;
	}
	Matrix operator -() {
		return *this * -1;
	}
	Matrix operator -(Matrix matrix) {
		return *this + -matrix;
	}
	Matrix operator *(Matrix matrix) {
		if (this->columns == matrix.rows) {
			Matrix ans(this->rows, matrix.columns);
			for (int r = 0; r < ans.rows; r++)
				for (int c = 0; c < ans.columns; c++) {
					T sum = T(0);
					for (int i = 0; i < this->columns; i++)
						sum += this->get(r, i) * matrix.get(i, c);
					ans.set(r, c, sum);
				}
			return ans;
		} else {
			return Matrix(T(0), T(0));
		}
	}

	template <typename U>
	operator Matrix<U>() {
		Matrix<U> ans(this->rows, this->columns);
		for (int r = 0; r < this->rows; r++)
			for (int c = 0; c <this->columns; c++)
				ans.set(r, c, U(this->get(r, c)));
		return ans;
	}

	template <typename U>
	friend std::ostream &operator <<(std::ostream &os, Matrix<U> matrix);

	template <typename U, typename V>
	friend Matrix<U> operator *(V scalar, Matrix<U> matrix);
};

template <typename T>
std::ostream &operator <<(std::ostream &os, Matrix<T> matrix) {
	for (int r = 0; r < matrix.rows; r++) {
		for (int c = 0; c < matrix.columns; c++) {
			if (c >= matrix.offsets[r] and c < matrix.offsets[r] + matrix.sizes[r]) {
				os.width(5);
				os << matrix.get(r, c) << " ";
			} else 
				os << "  (0) ";
		}
		os << std::endl;
	}
	return os;
}

template <typename T, typename U>
Matrix<T> operator *(U scalar, Matrix<T> matrix) {
	Matrix<T> ans(matrix.rows, matrix.columns);
	for (int r = 0; r < matrix.rows; r++)
		for (int c = 0; c < matrix.columns; c++)
			ans.set(r, c, scalar * matrix.get(r, c));
	return ans;
}

#endif