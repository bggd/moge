#ifndef MOGE_SRC_THREAD_MUTEX_WIN_HPP_INCLUDED
#define MOGE_SRC_THREAD_MUTEX_WIN_HPP_INCLUDED

#include <windows.h>

namespace moge {

struct MutexWin {

  CRITICAL_SECTION cs;

  void create() { InitializeCriticalSection(&this->cs); }

  void destroy() { DeleteCriticalSection(&this->cs); }

  void lock() { EnterCriticalSection(&this->cs); }

  void unlock() { LeaveCriticalSection(&this->cs); }

}; // struct MutexWin

} // namespace moge
#endif // MOGE_SRC_THREAD_MUTEX_WIN_HPP_INCLUDED
