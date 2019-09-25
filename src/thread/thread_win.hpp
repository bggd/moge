#ifndef MOGE_SRC_THREAD_THREAD_WIN_HPP_INCLUDED
#define MOGE_SRC_THREAD_THREAD_WIN_HPP_INCLUDED

#include <assert.h>
#include <process.h>
#include <windows.h>

namespace moge {

struct ThreadWin {
  uintptr_t handle = 0;

  void create(unsigned int (*fn)(void*), void* data) {
    assert(this->handle == 0);
    this->handle = _beginthreadex(NULL, 0, fn, data, 0, NULL);
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
