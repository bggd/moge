// clang-format off

#ifndef MOGE_DEBUG
#ifndef NDEBUG
#define MOGE_DEBUG (1)
#endif // NDEBUG
#endif // MOGE_DEBUG

#ifndef MOGE_ASSERT
  #ifdef NDEBUG
    #undef NDEBUG
    #include <assert.h>
    #define NDEBUG
  #else
    #include <assert.h>
  #endif
#define MOGE_ASSERT(c) assert(c)
#endif // MOGE_ASSERT

#ifndef MOGE_MALLOC
  #include <stdlib.h>
  #define MOGE_MALLOC(size) malloc(size)
#endif // MOGE_MALLOC

#ifndef MOGE_FREE
  #include <stdlib.h>
  #define MOGE_FREE(ptr) free(ptr)
#endif // MOGE_FREE

// clang-format on
