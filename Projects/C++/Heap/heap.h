#pragma once
#include <iostream>
#include <cstdint>
#include <iomanip>

#define COLUMNS 8

struct Heap {
  uint64_t size;
  uint8_t *data;
  uint8_t *heap_ptr;
  uint8_t *free_ptr;
  Heap() {
    this->data = nullptr;
  }
  Heap(uint64_t size) {
    this->size = size;
    this->data = new uint8_t[this->size];
    // first byte is left for null values
    this->heap_ptr = this->data;
    // free pointer is set to null
    this->free_ptr = this->data + size;
  }
  Heap(const Heap& h) {
    this->size = h.size;
    this->data = new uint8_t[this->size];
    this->heap_ptr = this->data + (h.heap_ptr - h.data);
    this->free_ptr = this->data + size;
    for (uint64_t i = 0; i < this->size; ++i)
      this->data[i] = h.data[i];
  }
  Heap operator =(const Heap& h) {
    delete[] this->data;
    this->size = h.size;
    this->data = new uint8_t[this->size];
    this->heap_ptr = this->data + (h.heap_ptr - h.data);
    this->free_ptr = this->data + (h.free_ptr - h.data);
    for (uint64_t i = 0; i < this->size; ++i)
      this->data[i] = h.data[i];
    return *this;
  }
  ~Heap() {
    delete[] this->data;
  }
  uint8_t *alloc(uint64_t size) {
    uint8_t *p = this->free_ptr;
    while (p < this->data + this->size) {
      if (*(p - 1) >= size) {
        this->free_ptr = (uint8_t *) *p;
        return p;
      }
      p = (uint8_t *) *p;
    }
    while ((size + 1) % 8) ++size;
    assert(this->heap_ptr + size + 1 <= this->data + this->size);
    *this->heap_ptr = size;
    uint8_t *alloc = ++this->heap_ptr;
    this->heap_ptr += size;
    return alloc;
  }
  template <class T>
  void dealloc(T *p) {
    *((uint8_t **) p) = this->free_ptr;
    this->free_ptr = (uint8_t *) p;
    std::cout << (unsigned long) this->free_ptr << " : " << (unsigned long) *this->free_ptr << std::endl;
  }
  friend std::ostream& operator <<(std::ostream& os, Heap h);
};

std::ostream& operator <<(std::ostream& os, Heap h) {
  for (uint64_t j = 0; j <= h.size / COLUMNS; ++j) {
    for (uint64_t i = 0; i < COLUMNS; ++i) {
      uint8_t *value = h.data + j * COLUMNS + i;
      if (value < h.data + h.size)
        os << (value == h.heap_ptr ? "H" : value == h.free_ptr ? "R" : " ") << std::setw(4) << std::hex << (unsigned int) *value << " ";
      if (value == h.free_ptr) std::cout << (value == h.free_ptr) << std::endl;
    }
    os << std::endl;
  }
  return os;
}
