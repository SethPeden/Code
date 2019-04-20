#pragma once

template <typename T>
class Complex {
  private:
    T real, imaginary;
  public:
    Complex(T real = 0, T imaginary = 0): real(real), imaginary(imaginary) { }
    Complex(const Complex &copy) {
      this->real = copy.real;
      this->imaginary = copy.imaginary;
    }
    Complex operator =(const Complex &copy) {
      Complex out;
      out.real = copy.real;
      out.imaginary = copy.imaginary;
      return out;
    }
    
}
