#pragma once

#include <initializer_list>
#include <iostream>
#include <cmath>

template <typename T, typename U>
T max(T, U);
template <typename T, typename U>
T min(T, U);

template <typename T>
struct vector {
  unsigned size;
  T *data;
  vector(unsigned size = 0) {
    this->data = new T[this->size = size];
  }
  vector(T *data, unsigned size) {
    this->data = new T[this->size = size];
    for (unsigned i = 0; i < this->size; ++i)
      this->data[i] = data[i];
  }
  vector(vector &copy) {
    this->data = new T[this->size = copy.size];
    for (unsigned i = 0; i < this->size; ++i)
      this->data[i] = copy.data[i];
  }
  vector(std::initializer_list<T> list) {
    this->data = new T[this->size = list.size()];
    for (auto i = list.begin(); i != list.end(); ++i)
      this->data[i - list.begin()] = *i;
  }
  ~vector() {
    delete[] this->data;
  }
  vector operator =(vector &copy) {
    delete[] this->data;
    this->data = new T[this->size = copy.size];
    for (unsigned i = 0; i < this->size; ++i)
      this->data[i] = copy.data[i];
    return *this;
  }
  vector operator =(std::initializer_list<T> list) {
    delete[] this->data;
    this->data = new T[this->size = list.size()];
    for (auto i = list.begin(); i != list.end(); ++i)
      this->data[i - list.begin()] = *i;
    return *this;
  }
  vector operator =(T s) {
    for (unsigned i = 0; i < this->size; ++i)
      this->data[i] = s;
    return *this;
  }
  vector append(T data) {
    T *old = this->data;
    unsigned old_size = this->size;
    this->data = new T[++this->size];
    for (unsigned i = 0; i < old_size; ++i)
      this->data[i] = old[i];
    this->data[old_size] = data;
    delete[] old;
    return *this;
  }
  vector operator +(T s) {
    vector out = *this;
    for (unsigned i = 0; i < this->size; ++i)
      out.data[i] += s;
    return out;
  }
  vector operator +(vector v) {
    vector out;
    if (this->size == v.size) {
      out = *this;
      for (unsigned i = 0; i < this->size; ++i)
        out.data[i] += v.data[i];
    }
    return out;
  }
  vector operator *(T s) {
    vector out = *this;
    for (unsigned i = 0; i < this->size; ++i)
      out.data[i] *= s;
    return out;
  }
  T dot(vector v) {
    T out = 0;
    for (unsigned i = 0; i < this->size; ++i)
      out += this->data[i] * v.data[i];
    return out;
  }
  vector operator -(T s) {
    return (*this + -1 * s);
  }
  vector operator -(vector v) {
    return (*this + -1 * v);
  }
  vector operator /(T s) {
    return 1 / s * *this;
  }
  vector operator ^(T s) {
    vector out(this->size);
    for (unsigned i = 0; i < this->size; ++i)
      out.data[i] = pow(this->data[i], s);
    return out;
  }
  vector operator ^(vector v) {
    vector out(this->size);
    for (unsigned i = 0; i < this->size; ++i)
      out.data[i] = pow(this->data[i], v.data[i]);
    return out;
  }
  T& operator [](unsigned i) {
    if (0 <= i && i < this->size)
      return this->data[i];
    return this->data[max(0, min(this->size - 1, i))];
  }
  vector operator [](vector<unsigned> i) {
    vector<unsigned> j = max(0, min(this->size - 1, i));
    vector out(i.size);
    for (unsigned k = 0; k < j.size; ++k)
      out[k] = this->data[j[k]];
    return out;
  }
  friend vector operator +(T s, vector v) {
    return v + s;
  }
  friend vector operator *(T s, vector v) {
    return v * s;
  }
  friend vector operator -(T s, vector v) {
    return -1 * v + s;
  }
  friend vector operator /(T s, vector v) {
    return (v ^ -1) * s;
  }
  friend vector operator ^(T s, vector v) {
    vector<T> out(v.size);
    out = s;
    return (out ^ v);
  }
  friend std::ostream &operator <<(std::ostream &os, vector v) {
    os << "[ ";
    for (unsigned i = 0; i < v.size - 1; ++i)
      os << v.data[i] << ", ";
    return (os << v.data[v.size - 1] << " ]");
  }
};

template <typename T, typename U>
T max(T a, U b) {
  if (a > b)
    return a;
  return b;
}
template <typename T, typename U>
vector<U> max(T a, vector<U> b) {
  vector<U> out = b;
  for (unsigned i = 0; i < b.size; ++i)
    out[i] = max(a, b[i]);
  return out;
}

template <typename T, typename U>
T min(T a, U b) {
  if (a > b)
    return b;
  return a;
}
template <typename T, typename U>
vector<U> min(T a, vector<U> b) {
  vector<U> out = b;
  for (unsigned i = 0; i < b.size; ++i)
    out[i] = min(a, b[i]);
  return out;
}
