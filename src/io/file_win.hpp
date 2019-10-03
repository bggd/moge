#ifndef MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED
#define MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED

#include <assert.h>
#include <stdint.h>
#include <windows.h>

namespace moge {

struct FileWin {

  HANDLE handle = 0;
  DWORD num_bytes = 0;

  void open(const char* path) {
    assert(this->handle == 0);
    this->handle = CreateFileA(path, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, NULL);
    assert(this->handle != 0);
    assert(this->handle != INVALID_HANDLE_VALUE);
    this->num_bytes = this->get_file_size();
  }

  void close() {
    assert(this->handle != 0 && this->handle != INVALID_HANDLE_VALUE);
    BOOL b = CloseHandle(this->handle);
    assert(b);
    this->handle = 0;
  }

  uint32_t get_file_size() {
    assert(this->handle != 0 && this->handle != INVALID_HANDLE_VALUE);
    DWORD r = GetFileSize(this->handle, NULL);
    assert(r != 0);
    assert(r != INVALID_FILE_SIZE);
    return r;
  }

  void* read() {
    DWORD readed_bytes;
    void* buffer = malloc(sizeof(char) * this->num_bytes + 1);
    assert(buffer);
    BOOL b =
        ReadFile(this->handle, buffer, this->num_bytes, &readed_bytes, NULL);
    assert(b);
    assert(this->num_bytes == readed_bytes);
    ((char*)buffer)[this->num_bytes] = '\0';
    return buffer;
  }
}; // struct FileWin

} // namespace moge

#endif // MOGE_SRC_IO_FILE_WIN_HPP_INCLUDED

