// Array.h
// Seth Peden
// March 3, 2018

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <initializer_list>

template <typename T>
class Array {
	int allocated, length;
	T *data;

public:
	Array() : allocated(0), length(0), data(nullptr) { }
	Array(int size) : length(0) {
		this->data = new T[this->allocated = 2 * size];
	}
	Array(const Array &copy) {
		this->data = new T[this->allocated = copy.allocated];
		this->length = copy.length;
		for (int i = 0; i < this->length; i++)
			this->data[i] = copy.data[i];
	}
	Array(std::initializer_list<T> data) {
		this->data = new T[this-> allocated = data.size() * 2];
		this->length = 0;
		for (T value : data)
			this->data[this->length++] = value;
	}
	~Array() {
		if (this->data) 
			delete[] this->data;
	}
	Array operator =(const Array &copy) {
		if (this->data) 
			delete[] this->data;
		this->data = new T[this->allocated = copy.allocated];
		this->length = copy.length;
		for (int i = 0; i < this->length; i++)
			this->data[i] = copy.data[i];
		return *this;
	}
	Array operator =(std::initializer_list<T> data) {
		if (this->data) 
			delete[] this->data;
		this->data = new T[this-> allocated = data.size() * 2];
		this->length = 0;
		for (T value : data)
			this->data[this->length++] = value;
		return *this;
	}
	Array operator +(T value) {
		Array temp = *this;
		if (double(++this->length) / this->allocated > 0.85) {
			if (this->data) 
				delete[] this->data;
			this->allocated = 2 * this->length;
			this->data = new T[this->allocated];
		}
		for (int i = 0; i < temp.length; i++)
			this->data[i] = temp.data[i];
		this->data[temp.length] = value;
		return *this;
	}
	void operator +=(T value) {
		*this = *this + value;
	}
	Array operator +(Array values) {
		for (int i = 0; i < values.length; i++)
			*this += values.data[i];
		return *this;
	}
	void operator +=(Array values) {
		*this = *this + values;
	}
	bool contains(T value) {
		bool ans = false;
		for (int i = 0; i < this->length; i++)
			if ((ans = this->data[i] == value))
				break;
		return ans;
	}
	void remove(T value) {
		bool swap = false;
		for (int i = 0; i < this->length; i++) {
			if (!swap and this->data[i] == value)
				swap = true;
			if (swap and i + 1 < this->length)
				this->data[i] = this->data[i + 1];
		}
		if (swap)
			--this->length;
	}
	int removeAll(T value) {
		int ans = 0;
		while (this->contains(value)) {
			this->remove(value);
			++ans;
		}
		return ans;
	}
	T remove(int index, bool isIndex) {
		if (index < this->length) {
			T ans = this->data[index];
			for (int i = index; i < this->length - 1; i++)
				this->data[i] = this->data[i + 1];
			--this->length;
			return ans;
		}
		std::cout << "Array::ERROR: Index to remove is out of bounds. [Index = " << index << "]" << std::endl;
		return T(0);
	}
	T &operator [](int index) {
		return this->data[index];
	}
	int size() {
		return this->length;
	}
	Array<T> reverse() {
		Array ans;
		for (int i = this->length - 1; i >= 0; i--)
			ans += this->data[i];
		return ans;
	}

	template <typename U>
	friend std::ostream &operator <<(std::ostream &os, Array<U> array);

};

template <typename U>
std::ostream &operator <<(std::ostream &os, Array<U> array) {
	os << "[ ";
	for (int i = 0; i < array.length - 1; i++)
		os << array.data[i] << ", ";
	if (array.length) 
		os << array.data[array.length - 1] << " ";
	os << "]";
	return os;
}

#endif