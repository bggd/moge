#ifndef MOGE_DEBUG
#ifndef NDEBUG
#define MOGE_DEBUG (1)
#endif // NDEBUG
#endif // MOGE_DEBUG

#ifndef MOGE_ASSERT
#include <assert.h>
#define MOGE_ASSERT(c) assert(c)
#endif // MOGE_ASSERT
