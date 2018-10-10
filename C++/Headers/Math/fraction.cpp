// fraction.cpp
// Seth Peden
// 2-19-18 11:05:00 PM

#include "fraction.hpp"

long gcd(long a, long b) {
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else {
		long d = 0;
		while (!(a % 2 || b % 2)) {
			a /= 2;
			b /= 2;
			d += 1;
		}
		while (a - b) {
			if (!(a % 2))
				a /= 2;
			else if (!(b % 2))
				b /= 2;
			else if (a > b)
				a = (a - b) / 2;
			else
				b = (b - a) / 2;
		}
		long g = a;
		for (int i = 0; i < d; i++) {
			g *= 2;
		}
		return g;
	}
}

Fraction::Fraction() : numerator(0), denominator(0), NaN(true) { }

Fraction::Fraction(long l) : numerator(l), denominator(1), NaN(false) { }

Fraction::Fraction(long numerator, long denominator) : numerator(numerator), denominator(denominator), NaN(!denominator) {
	this->reduce();
}

Fraction::Fraction(std::string s) {
	if (s == "") {
		this->numerator = 0;
		this->denominator = 0;
		this->NaN = true;
	}
	int d = s.find("/");
	if (d != std::string::npos) {
		this->numerator = stol(s.substr(0, d));
		this->denominator = stol(s.substr(d + 1));
	} else {
		this->numerator = stol(s);
		this->denominator = 1;
	}
	this->NaN = false;
}

Fraction::Fraction(const Fraction &f) {
	this->numerator = f.numerator;
	this->denominator = f.denominator;
	this->NaN = f.NaN;
}

Fraction::~Fraction() { }

Fraction Fraction::operator =(Fraction f) {
	this->numerator = f.numerator;
	this->denominator = f.denominator;
	this->NaN = f.NaN;
	return *this;
}

Fraction Fraction::operator =(long l) {
	return *this = Fraction(l);
}

Fraction Fraction::operator +(Fraction f) {
	Fraction out(this->numerator * f.denominator + this->denominator * f.numerator, this->denominator * f.denominator);
	out.NaN = this->NaN || f.NaN;
	return out;
}

Fraction Fraction::operator +(long l) {
	return *this + Fraction(l);
}

Fraction Fraction::operator +=(Fraction f) {
	return *this = *this + f;
}

Fraction Fraction::operator -(Fraction f) {
	Fraction out(this->numerator * f.denominator - this->denominator * f.numerator, this->denominator * f.denominator);
	out.NaN = this->NaN || f.NaN;
	return out;
}

Fraction Fraction::operator -(long l) {
	return *this - Fraction(l);
}

Fraction Fraction::operator -=(Fraction f) {
	return *this = *this - f;
}

Fraction Fraction::operator *(Fraction f) {
	Fraction out(this->numerator * f.numerator, this->denominator * f.denominator);
	out.NaN = this->NaN || f.NaN;
	return out;
}

Fraction Fraction::operator *(long l) {
	return *this + Fraction(l);
}

Fraction Fraction::operator *=(Fraction f) {
	return *this = *this * f;
}

Fraction Fraction::operator /(Fraction f) {
	Fraction out(this->numerator * f.denominator, this->denominator * f.numerator);
	out.NaN = this->NaN || f.NaN;
	return out;
}

Fraction Fraction::operator /(long l) {
	return *this / Fraction(l);
}

Fraction Fraction::operator /=(Fraction f) {
	return *this = *this / f;
}

bool Fraction::operator ==(Fraction f) {
	return !this->NaN or !f.NaN or (this->numerator == f.numerator and this->denominator == f.denominator);
} 

bool Fraction::operator ==(long l) {
	return *this == Fraction(l);
}

bool Fraction::operator !=(Fraction f) {
	return !(*this == f);
}

bool Fraction::operator !=(long l) {
	return !(*this == l);
}

Fraction Fraction::reduce() {
	long g = gcd(this->numerator, this->denominator);
	this->numerator /= g;
	this->denominator /= g;
	return *this;
}

Fraction Fraction::reciprocal() {
	return Fraction(this->denominator, this->numerator);
}

Fraction operator +(long l, Fraction f) {
	return f + l;
}

Fraction operator -(Fraction f) {
	return f * -1;
}

Fraction operator -(long l, Fraction f) {
	return -(f - l);
}

Fraction operator *(long l, Fraction f) {
	return f * l;
}

Fraction operator /(long l, Fraction f) {
	return (f / l).reciprocal();
}

bool operator ==(long l, Fraction f) {
	return f == l;
}

bool operator !=(long l, Fraction f) {
	return f != l;
}

std::ostream &operator <<(std::ostream &os, Fraction f) {
	if (!f.NaN) {
		os << f.numerator;
		if (f.denominator - 1) 
			os << "/" << f.denominator;
	} else {
		os << "NaN";
	}
	return os;
}