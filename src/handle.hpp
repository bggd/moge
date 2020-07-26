#ifndef MOGE_SRC_HANDLE_HPP_INCLUDED
#define MOGE_SRC_HANDLE_HPP_INCLUDED

#include <stdint.h>

namespace moge {

struct Handle {
  uint32_t id;
  uint32_t generation;
};

} // namespace moge

#endif // MOGE_SRC_HANDLE_HPP_INCLUDED
