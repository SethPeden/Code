#ifndef HEAP_H
#define HEAP_H

// Heap.h
// Seth Peden
// March 16, 2018

#include <iostream>
#include <initializer_list>
#include "Array.h"

template <typename T>
class Heap {
	Array<T> data;
	void bubbleDown(int i) {
		if (i < this->data.size()) {
			int l = 2 * i + 1, r = 2 * i + 2;
			T temp = this->data[i];
			T *swap = nullptr;
			T swapIndex = -1;
			if (l < this->data.size() and r < this->data.size()) {
				if (this->data[l] < this->data[r] and temp < this->data[r]) {
					swap = &this->data[r];
					swapIndex = r;
				} else if (temp < this->data[l]) {
					swap = &this->data[l];
					swapIndex = l;
				}
			} else if (l < this->data.size() and temp < this->data[l]) {
				swap = &this->data[l];
				swapIndex = l;
			} else if (r < this->data.size() and temp < this->data[r]) {
				swap = &this->data[r];
				swapIndex = r;
			}
			if (swap) this->data[i] = *swap;
			if (swap) *swap = temp;
			if (swapIndex > -1) this->bubbleDown(swapIndex);
		}
	}
	void bubbleUp(int i) {
		if (i < this->data.size()) {
			T temp = this->data[i];
			int p = (i - 1) / 2;
			if (temp > this->data[p]) {
				this->data[i] = this->data[p];
				this->data[p] = temp;
				this->bubbleUp(p);
			}
		}
	}

public:
	Heap() { }
	Heap(Array<T> data) {
		this->data = data;
		for (int i = this->data.size() / 2; i >= 0; i--)
			bubbleDown(i);
	}
	Heap(std::initializer_list<T> data) {
		this->data = data;
		for (int i = this->data.size() / 2; i >= 0; i--)
			bubbleDown(i);
	}
	T deleteMax() {
		T ans = this->data[0];
		this->data[0] = this->data.remove(this->data.size() - 1, true);
		this->bubbleDown(0);
		return ans;
	}
	void insert(T value) {
		this->data += value;
		this->bubbleUp(this->data.size() - 1);
	}
	int size() {
		return this->data.size();
	}
	static Array<T> sort(Array<T> data) {
		Array<T> ans;
		Heap heap = data;
		while (heap.size())
			ans += heap.deleteMax();
		return ans;
	}

	template <typename U>
	friend std::ostream &operator <<(std::ostream &os, Heap<U> heap);

};

template <typename U>
std::ostream &operator <<(std::ostream &os, Heap<U> heap) {
	os << heap.data;
	return os;
}

#endif