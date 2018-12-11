#pragma once

#include <initializer_list>

template <typename T>
class Vector {
  private:
    unsigned long size;
    T *data;
  public:
    Vector(unsigned long size = 0): size(size) { }
    Vector(std::initializer_list<T> list) {
      this->data = new T[this->size = list.size()];
      unsigned long i = 0;
      for (T l : list) this->data[i++] = l;
    }
    Vector(const Vector &copy) {
      this->data = new T[this->size = copy.size];
      for (unsigned long i = 0; i < this->size; ++i) this->data[i] = copy.data[i];
    }
    Vector operator =(const Vector &copy) {
      delete this->data;
      return (*this = Vector(copy));
    }
    ~Vector() {
      delete this->data;
    }
    T &operator [](unsigned long index) {
      if (index >= 0 && index < this->size) return this->data[index];
      return T(0);
    }
    friend std::ostream &operator
};
