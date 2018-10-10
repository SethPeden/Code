// Array.h
// Seth Peden
// March 7, 2018

#ifndef STACK_H
#define STACK_H

template <class T>
class Stack {
	int _size;
	T   *top;
public:
	Stack() : _size(0), top(nullptr) { }
	Stack(const Stack &copy) {
		this->top = new T[this->_size = copy._size];
		for (int i = 0; i < copy._size; i++)
			this->top[i] = copy.top[i];
	}
	~Stack() {
		delete[] this->top;
	}
	Stack operator =(const Stack &copy) {
		delete[] this->top;
		this->top = new T[this->_size = copy._size];
		for (int i = 0; i < copy._size; i++)
			this->top[i] = copy.top[i];
	}
	void push(T val) {
		Stack temp = *this;
		delete[] this->top;
		this->top = new T[++this->_size];
		for (int i = 1; i < this->_size; i++) 
			this->top[i] = temp.top[i - 1];
		this->top[0] = val;
	}
	T pop() {
		T val = this->top[0];
		for (int i = 0; i < this->_size - 1; i++)
			this->top[i] = this->top[i + 1];
		--this->_size;
		return val;
	}
	T peak(int i) {
		return this->top[i];
	}
	int size() {
		return this->_size;
	}
	template <class NewT>
	operator Stack<NewT>() {
		Stack copy = *this;
		Stack<NewT> result;
		for (int i = this->size() - 1; i >= 0; i--) {
			cout << this->peak[i];
			// result.push(NewT(this->peak[i]));
		}
		return result;
	}
};

template <class T>
ostream &operator << (ostream &os, Stack<T> stack) {
	cout << "[ ";
	while (stack.size() > 1)
		cout << stack.pop() << ", ";
	cout << stack.pop() << " ]";
	return os;
}

#endif