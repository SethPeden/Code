// main.cpp
// Seth Peden
// March 13, 2018

#include <iostream>
#include "Matrix.h"
using namespace std;

int main() {
	Matrix<int> m1(1, 3);
	m1.set(0, 0, 1);
	m1.set(0, 1, 2);
	m1.set(0, 2, 3);
	cout << m1 << endl;

	Matrix<int> m2(3, 2);
	m2.set(0, 0, 1);
	m2.set(0, 1, 2);
	m2.set(1, 0, 3);
	m2.set(1, 1, 4);
	m2.set(2, 0, 5);
	m2.set(2, 1, 6);
	cout << m2 << endl;

	cout << m1 * m2 << endl;
	return 0;
}