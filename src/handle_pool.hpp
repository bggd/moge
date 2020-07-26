#ifndef MOGE_SRC_HANDLE_POOL_HPP_INCLUDED
#define MOGE_SRC_HANDLE_POOL_HPP_INCLUDED

#include "handle.hpp"

namespace moge {

template <typename T>
struct HandlePool {
  T* objects;
  Handle* handles;
  bool* use_handles;
  uint32_t capacity;

  void createHandlePool(uint32_t _capacity) {
    MOGE_ASSERT(!this->objects);
    MOGE_ASSERT(!this->handles);
    MOGE_ASSERT(!this->use_handles);
    MOGE_ASSERT(!this->capacity);

    this->objects = static_cast<T*>(MOGE_MALLOC(sizeof(T) * _capacity));
    MOGE_ASSERT(this->objects);

    this->handles = static_cast<moge::Handle*>(MOGE_MALLOC(sizeof(moge::Handle) * _capacity));
    MOGE_ASSERT(this->handles);

    this->use_handles = static_cast<bool*>(MOGE_MALLOC(sizeof(bool) * _capacity));
    MOGE_ASSERT(this->use_handles);

    memset(this->use_handles, false, sizeof(bool) * _capacity);

    this->capacity = _capacity;
  }

  void destroyHandlePool() {
    MOGE_ASSERT(this->objects);
    MOGE_ASSERT(this->handles);
    MOGE_ASSERT(this->use_handles);
    MOGE_ASSERT(this->capacity);

    MOGE_FREE(this->objects);
    MOGE_FREE(this->handles);
    MOGE_FREE(this->use_handles);

    this->objects = NULL;
    this->handles = NULL;
    this->use_handles = NULL;

    this->capacity = 0;
  }

  Handle insertObject(T& obj) {
    for (uint32_t i = 0; i < this->capacity; ++i) {
      if (!this->use_handles[i]) {
        this->objects[i] = obj;
        this->handles[i].id = i;
        this->handles[i].generation++;
        this->use_handles[i] = true;
        return this->handles[i];
      }
    }
    MOGE_ASSERT(!"moge::HandlePool ERROR: couldn't find a free handle");
    moge::Handle unreach = {};
    return unreach;
  }

  void removeHandle(Handle& handle) {
    MOGE_ASSERT(handle.id < this->capacity);
    moge::Handle& request = this->handles[handle.id];
    MOGE_ASSERT(request.id == handle.id);
    MOGE_ASSERT(request.generation == handle.generation);
    MOGE_ASSERT(this->use_handles[handle.id]);
    this->use_handles[handle.id] = false;
  }

  T* getObject(Handle& handle) {
    MOGE_ASSERT(handle.id < this->capacity);
    moge::Handle& request = this->handles[handle.id];
    MOGE_ASSERT(request.id == handle.id);
    MOGE_ASSERT(request.generation == handle.generation);
    MOGE_ASSERT(this->use_handles[handle.id]);
    return &this->objects[handle.id];
  }
};

} // namespace moge

#endif // MOGE_SRC_HANDLE_POOL_HPP_INCLUDED
