#ifndef CPPES8_SRC_HANDLE_HPP_INCLUDED
#define CPPES8_SRC_HANDLE_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>

namespace cppes8 {
namespace handle {

struct Handle {
  uint32_t id = UINT32_MAX;
  uint32_t generation = UINT32_MAX;
};

template <typename T, uint32_t N>
struct HandlePool {
  T objects[N] = {};
  Handle handles[N] = {};
  bool use_handles[N] = {};

  Handle insert(T obj);
  void remove(Handle handle);
  T* get(Handle handle);
};

} // namespace handle
} // namespace cppes8

template <typename T, uint32_t N>
cppes8::handle::Handle cppes8::handle::HandlePool<T, N>::insert(T obj) {
  for (uint32_t i = 0; i < N; ++i) {
    if (!this->use_handles[i]) {
      this->objects[i] = obj;
      this->handles[i].id = i;
      this->handles[i].generation++;
      this->use_handles[i] = true;
      return this->handles[i];
    }
  }
  assert(!"HandlePool ERROR: couldn't find a free handle.");
  return cppes8::handle::Handle{};
}

template <typename T, uint32_t N>
void cppes8::handle::HandlePool<T, N>::remove(cppes8::handle::Handle handle) {
  assert(handle.id < N);
  cppes8::handle::Handle& request = this->handles[handle.id];
  assert(request.id == handle.id);
  assert(request.generation == handle.generation);
  assert(this->use_handles[handle.id]);
  this->use_handles[handle.id] = false;
}

template <typename T, uint32_t N>
T* cppes8::handle::HandlePool<T, N>::get(cppes8::handle::Handle handle) {
  assert(handle.id < N);
  cppes8::handle::Handle& request = this->handles[handle.id];
  assert(request.id == handle.id);
  assert(request.generation == handle.generation);
  assert(this->use_handles[handle.id]);
  return &this->objects[handle.id];
}

#endif // CPPES8_SRC_HANDLE_HPP_INCLUDED
