#include "sdl.hpp"
#include <SDL_syswm.h>

#include "../macro.hpp"

void moge::sdl::createSDL(SDLContext& ctx) {
  MOGE_ASSERT(! ctx.window);

#if defined(MOGE_DEBUG)
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

  int err = SDL_Init(SDL_INIT_EVERYTHING);
  MOGE_ASSERT(err == 0);

  ctx.window = SDL_CreateWindow("sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  MOGE_ASSERT(ctx.window);
}

void moge::sdl::destroySDL(SDLContext& ctx) {
  MOGE_ASSERT(ctx.window);
  SDL_DestroyWindow(ctx.window);
  ctx.window = NULL;
  SDL_Quit();
}

HWND moge::sdl::getHWND(SDLContext& ctx) {
  MOGE_ASSERT(ctx.window);
  SDL_SysWMinfo si;
  SDL_VERSION(&si.version);
  SDL_bool b = SDL_GetWindowWMInfo(ctx.window, &si);
  MOGE_ASSERT(b == SDL_TRUE);
  MOGE_ASSERT(si.subsystem == SDL_SYSWM_WINDOWS);
  return si.info.win.window;
}
