#ifndef MOGE_SRC_THREAD_THREAD_WIN_HPP_INCLUDED
#define MOGE_SRC_THREAD_THREAD_WIN_HPP_INCLUDED

#include <assert.h>
#include <process.h>
#include <stdint.h>
#include <windows.h>

namespace moge {

struct ThreadWin {

private:
  uintptr_t handle = 0;
  void (*fn)(void*) = nullptr;
  void* data = nullptr;

public:
  void create(void (*fn)(void*), void* data) {
    static unsigned int (*thread_fn)(void*) = [](void* d) -> unsigned int {
      ThreadWin* thr = (ThreadWin*)d;
      thr->fn(thr->data);
      return 0;
    };

    assert(fn);
    assert(this->handle == 0);
    this->fn = fn;
    this->data = data;
    this->handle = _beginthreadex(NULL, 0, thread_fn, this, 0, NULL);
    assert(this->handle);
  }

  void destroy() {
    assert(this->handle);
    CloseHandle((HANDLE)this->handle);
  }

  void join() {
    assert(this->handle);
    WaitForSingleObject((HANDLE)this->handle, INFINITE);
  }

}; // struct ThreadWin

} // namespace moge

#endif // MOGE_SRC_THREAD_THREAD_WIN_HPP_INCLUDED
