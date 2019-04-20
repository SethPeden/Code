// Array.h
// Seth Peden
// March 3, 2018

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

template <class T>
class Array {

private:
	int _size;
	T *values;

public:
	Array() : _size(0), values(nullptr) { }
	Array(int size, T* values) {
		this->_size = size;
		this->values = new T[this->_size];
		for (int i = 0; i < this->_size; i++)
			this->values[i] = values[i]; 
	}
	Array(initializer_list<T> values) {
		this->_size = 0;
		for (T value : values)
			this->add(value);
	}
	Array(const Array &copy) {
		this->_size = copy._size;
		this->values = new T[this->_size];
		for (int i = 0; i < this->_size; i++) 
			this->values[i] = copy.values[i];
	}
	~Array() {
		delete[] this->values;
	}
	Array operator =(const Array &copy) {
		delete[] this->values;
		this->_size = copy._size;
		this->values = new T[this->_size];
		for (int i = 0; i < this->_size; i++) 
			this->values[i] = copy.values[i];
		return *this;
	}
	Array operator =(initializer_list<T> &values) {
		delete[] this->values;
		this->_size = values.size();
		for (T value : values)
			this->add(value);
		return *this;
	}
	Array add(T value) {
		Array old = *this;
		delete[] this->values;
		this->values = new T[++this->_size];
		for (int i = 0; i < old._size; i++) 
			this->values[i] = old.values[i];
		this->values[old._size] = value;
		return *this;
	}
	Array operator +(T value) {
		Array a = *this;
		return a.add(value);
	}
	Array operator +=(T value) {
		return this->add(value);
	}
	Array add(Array<T> array) {
		Array old = *this;
		delete[] this->values;
		this->values = new T[this->_size = this->_size + array._size];
		for (int i = 0; i < old._size; i++)
			this->values[i] = old.values[i];
		for (int i = 0; i < array._size; i++) 
			this->values[old._size + i] = array.values[i];
		return *this;
	}
	Array operator +(Array array) {
		Array a = *this;
		return a.add(array);
	}
	Array operator +=(Array array) {
		return this->add(array);
	}
	Array add(initializer_list<T> values) {
		for (T value : values)
			this->add(value);
		return *this;
	}
	Array operator +=(initializer_list<T> values) {
		return this->add(values);
	}
	T remove(int index) {
		Array old = *this;
		delete[] this->values;
		this->values = new T[--this->_size];
		for (int i = 0; i < index; i++)
			this->values[i] = old.values[i];
		T out = old[index];
		for (int i = index + 1; i < old._size; i++)
			this->values[i - 1] = old.values[i];
		return out;
	}
	T *remove(int *indices, int count) {
		T *out = new T[count];
		Array<T> old = *this;
		delete[] this->values;
		this->values = new T[this->_size = this->_size - count];
		int dec = 0;
		for (int i = 0; i < old._size; i++) {
			int flag = 1;
			for (int j = 0; j < count; j++) {
				if (i == indices[j]) {
					++dec;
					flag = 0;
				}
			}
			if (flag)
				this->values[i - dec] = old[i];
		}
		return out;
	}
	T *remove(initializer_list<int> indices) {
		T *out = new T[indices.size()];
		Array<T> old = *this;
		delete[] this->values;
		this->values = new T[this->_size = this->_size - indices.size()];
		int dec = 0;
		for (int i = 0; i < old._size; i++) {
			int flag = 1;
			for (int j : indices) {
				if (i == j) {
					++dec;
					flag = 0;
				}
			}
			if (flag)
				this->values[i - dec] = old[i];
		}
		return out;
	}
	T operator [](int index) {
		return this->values[index];
	}
	int size() {
		return this->_size;
	}
	Array reverse() {
		Array array = *this;
		for (int i = 0; i < this->_size; i++)
			array[this->_size - i - 1] = this[i];
	}
};

template <class T>
ostream &operator <<(ostream &os, Array<T> array) {
	os << "[ ";
	for (int i = 0; i < array.size() - 1; i++)
		os << array[i] << ", ";
	if (array.size())
		os << array[array.size() - 1] << " ";
	os << "]";
	return os;
}

template <>
ostream &operator <<<string>(ostream &os, Array<string> array) {
	os << "[ ";
	for (int i = 0; i < array.size() - 1; i++)
		os << "\"" << array[i] << "\"" << ", ";
	if (array.size())
		os << "\"" << array[array.size() - 1] << "\"" << " ";
	os << "]";
	return os;
}

template <>
ostream &operator <<<char>(ostream &os, Array<char> array) {
	os << "[ ";
	for (int i = 0; i < array.size() - 1; i++)
		os << "\'" << array[i] << "\'" << ", ";
	if (array.size())
		os << "\'" << array[array.size() - 1] << "\'" << " ";
	os << "]";
	return os;
}

template <>
ostream &operator <<<unsigned char>(ostream &os, Array<unsigned char> array) {
	os << "[ ";
	for (int i = 0; i < array.size() - 1; i++)
		os << hex << int(array[i]) << ", ";
	if (array.size())
		os << hex << int(array[array.size() - 1]) << " ";
	os << "]";
	return os;
}

template <class T>
Array<T> operator +(T value, Array<T> array) {
	Array<T> out = Array<T>(1, &value);
	return out + array;
}

#endif