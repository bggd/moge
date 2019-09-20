#ifndef MOGE_SRC_FIXED_ARRAY_HPP_INCLUDED
#define MOGE_SRC_FIXED_ARRAY_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

namespace moge {

template <typename T>
struct FixedArray {
  T* ptr = NULL;
  size_t len = 0;

  void reserve(size_t num) {
    assert(this->ptr == NULL);
    assert(this->len == 0);
    this->ptr = (T*)malloc(sizeof(T) * num);
    assert(this->ptr);
    this->len = num;
  }

  void free_mem() {
    assert(this->ptr);
    assert(this->len);
    free(this->ptr);
    this->ptr = NULL;
    this->len = 0;
  }

  T& operator[](size_t idx) {
    assert(this->ptr);
    assert(idx < this->len);
    return this->ptr[idx];
  }

  const T& operator[](size_t idx) const {
    assert(this->ptr);
    assert(idx < this->len);
    return this->ptr[idx];
  }

  void fill(T v) {
    assert(this->ptr);
    assert(this->len);
    for (size_t i = 0; i < this->len; ++i) {
      this->ptr[i] = v;
    }
  }
}; // struct FixedArray<T>

} // namespace moge

#endif // MOGE_SRC_FIXED_ARRAY_HPP_INCLUDED
