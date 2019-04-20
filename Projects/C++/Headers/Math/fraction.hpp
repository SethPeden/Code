// fraction.hpp
// Seth Peden
// 2-19-18 11:05:00 PM

#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <string>

class Fraction {

private:
	// Members
	long numerator, denominator;
	bool NaN;

	// Functions
	Fraction reduce();

public:
	// Constructors
	Fraction();
	Fraction(long);
	Fraction(long, long);
	Fraction(std::string);
	Fraction(const Fraction &);
	// Destructor
	~Fraction();
	// Operators
	Fraction operator =(Fraction);
	Fraction operator =(long);
	Fraction operator +(Fraction);
	Fraction operator +(long);
	Fraction operator +=(Fraction);
	Fraction operator -(Fraction);
	Fraction operator -(long);
	Fraction operator -=(Fraction);
	Fraction operator *(Fraction);
	Fraction operator *(long);
	Fraction operator *=(Fraction);
	Fraction operator /(Fraction);
	Fraction operator /(long);
	Fraction operator /=(Fraction);
	bool operator ==(Fraction);
	bool operator ==(long);
	bool operator !=(Fraction);
	bool operator !=(long);

	// Functions
	Fraction reciprocal();

	// Friends
	friend Fraction reduce(Fraction);
	friend std::ostream& operator <<(std::ostream &, Fraction);

};

// Static Functions
Fraction operator +(long, Fraction);
Fraction operator -(Fraction);
Fraction operator -(long, Fraction);
Fraction operator *(long, Fraction);
Fraction operator /(long, Fraction);
bool operator ==(long, Fraction);
bool operator !=(long, Fraction);
std::ostream &operator <<(std::ostream &os, Fraction);

#endif