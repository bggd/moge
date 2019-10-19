#ifndef MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED
#define MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>
#include <windows.h>

namespace moge {

struct FileWin {

  HANDLE handle = 0;
  DWORD num_bytes = 0;
};

void file_win_open(FileWin* f, const char* path) {
  assert(f->handle == 0);
  f->handle = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  assert(f->handle != 0);
  assert(f->handle != INVALID_HANDLE_VALUE);
  f->num_bytes = GetFileSize(f->handle, NULL);
  assert(f->num_bytes != 0);
  assert(f->num_bytes != INVALID_FILE_SIZE);
}

void file_win_close(FileWin* f) {
  assert(f->handle != 0 && f->handle != INVALID_HANDLE_VALUE);
  BOOL b = CloseHandle(f->handle);
  assert(b);
  f->handle = 0;
  f->num_bytes = 0;
}

uint32_t file_win_get_file_size(FileWin* f) {
  assert(f->handle != 0 && f->handle != INVALID_HANDLE_VALUE);
  return f->num_bytes;
}

void file_win_read(FileWin* f, void* dst) {
  assert(f->handle != 0 && f->handle != INVALID_HANDLE_VALUE);
  assert(f->num_bytes > 0);
  assert(dst);
  DWORD readed_bytes;
  BOOL b = ReadFile(f->handle, dst, f->num_bytes, &readed_bytes, NULL);
  assert(b);
  assert(f->num_bytes == readed_bytes);
}

} // namespace moge

#endif // MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED

