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
