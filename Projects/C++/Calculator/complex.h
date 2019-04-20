#pragma once
#include <iostream>
#include <string>
#include <regex>
#include "pattern.h"

typedef struct Complex {
	double real, imaginary;
	bool NaN;
	Complex(double real = 0, double imaginary = 0, bool NaN = true) : real(real), imaginary(imaginary), NaN(NaN) { }
	Complex(std::string input) {
		while (input.find(" ") != std::string::npos)
			input = input.replace(input.find(" "), 1, "");
		if ((" ?" + Patterns::Real + " ?").matches(input)) {
			this->NaN = false;
			this->real = stod(input);
			this->imaginary = 0;
		} else if ((" ?" + Patterns::Imaginary + " ?").matches(input)) {
			this->NaN = false;
			this->real = 0;
			if (input == "i")
				this->imaginary = 1;
			else if (input == "-i")
				this->imaginary = -1;
			else
				this->imaginary = stod(input);
		} else if ((" ?" + Patterns::Complex + " ?").matches(input)) {
			this->NaN = false;
			std::string::size_type index;
			this->real = stod(input, &index);
			if (input.substr(index) == "+i")
				this->imaginary = 1;
			else if (input.substr(index) == "-i")
				this->imaginary = -1;
			else
				this->imaginary = stod(input.substr(index));
		} else {
			this->NaN = true;
		}
	}
	double magnitude() {
		return this->real * this->real + this->imaginary * this->imaginary;
	}
	Complex conjugate() {
		return Complex(this->real, -this->imaginary, this->NaN);
	}
	Complex operator +(Complex complex) {
		return Complex(this->real + complex.real, this->imaginary + complex.imaginary, this->NaN | complex.NaN);
	}
	Complex operator -(Complex complex) {
		return Complex(this->real - complex.real, this->imaginary - complex.imaginary, this->NaN | complex.NaN);
	}
	Complex operator *(Complex complex) {
		return Complex(this->real * complex.real - this->imaginary * complex.imaginary,
									 this->imaginary * complex.real + complex.imaginary * this->real,
									 this->NaN | complex.NaN);
	}
	Complex operator /(double scalar) {
		return Complex(this->real / scalar, this->imaginary / scalar, this->NaN);
	}
	Complex operator /(Complex complex) {
		return (*this * complex.conjugate()) / (complex * complex.conjugate()).real;
	}
} Complex;

std::ostream &operator <<(std::ostream &os, Complex complex) {
	if (complex.NaN)
		return (os << "NaN");
	if (complex.real != 0) {
		os << complex.real;
		if (complex.imaginary > 0) {
			os << " + ";
			if (complex.imaginary != 1)
				os << complex.imaginary;
			os << "i";
		} else if (complex.imaginary < 0) {
			os << " - ";
			if (complex.imaginary != -1)
				os << -complex.imaginary;
			os << "i";
		}
	} else if (complex.imaginary != 0) {
		if (complex.imaginary > 0) {
			if (complex.imaginary != 1)
				os << complex.imaginary;
			os << "i";
		} else if (complex.imaginary < 0) {
			os << "-";
			if (complex.imaginary != -1)
				os << -complex.imaginary;
			os << "i";
		}
	} else {
		os << 0;
	}
	return os;
}