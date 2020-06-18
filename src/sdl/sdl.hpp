#ifndef MOGE_SRC_SDL_SDL_HPP_INCLUDED
#define MOGE_SRC_SDL_SDL_HPP_INCLUDED

#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace moge {
namespace sdl {

struct SDLContext {
  SDL_Window* window;
};

void createSDL(SDLContext& ctx);
void destroySDL(SDLContext& ctx);
HWND getHWND(SDLContext& ctx);

} // namespace sdl
} // namespace moge

#endif // MOGE_SRC_SDL_SDL_HPP_INCLUDED
