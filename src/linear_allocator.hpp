#ifndef MOGE_SRC_LINEAR_ALLOCATOR_HPP_INCLUDED
#define MOGE_SRC_LINEAR_ALLOCATOR_HPP_INCLUDED

#include <assert.h>
#include <stdlib.h>

namespace moge {

struct LinearAllocator {
  char* start = NULL;
  char* end = NULL;
  char* current = NULL;

  void reserve(size_t num) {
    assert(this->start == NULL && this->end == NULL && this->current == NULL);
    this->start = (char*)malloc(sizeof(char) * num);
    this->current = this->start;
    this->end = this->start + sizeof(char) * num;
  }

  void free_mem() {
    assert(this->start && this->end && this->current);
    free(this->start);
    this->start = NULL;
    this->end = NULL;
    this->current = NULL;
  }

  template <typename T>
  T* alloc(size_t num = 1) {
    assert(this->start && this->end && this->current);
    assert(num);
    T* p = (T*)this->current;
    this->current += sizeof(T) * num;
    assert(this->current <= this->end);
    return p;
  }

  void reset() {
    assert(this->start && this->end && this->current);
    this->current = this->start;
  }
}; // struct LinearAllocator

} // namespace moge

#endif // MOGE_SRC_LINEAR_ALLOCATOR_HPP_INCLUDED
