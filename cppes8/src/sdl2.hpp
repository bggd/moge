#ifndef CPPES8_SRC_SDL2_HPP_INCLUDED
#define CPPES8_SRC_SDL2_HPP_INCLUDED

#ifdef __MINGW32__
#define SDL_MAIN_HANDLE
#endif

#include <SDL.h>
#include <SDL_syswm.h>
#include <assert.h>
#include <stdbool.h>

namespace cppes8 {

namespace sdl2 {

struct SDL2 {
  SDL_Window* window = nullptr;
  bool has_close_request = false;
};

void init(SDL2&);
void shutdown(SDL2&);
bool poll_event(SDL2&, SDL_Event*);
HWND get_hwnd(SDL2&);

} // namespace sdl2
} // namespace cppes8

void cppes8::sdl2::init(cppes8::sdl2::SDL2& self) {
  assert(self.window == nullptr);
  assert(self.has_close_request == false);

#ifdef _DEBUG
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

  int err = SDL_Init(SDL_INIT_EVERYTHING);
  assert(err == 0);

  self.window = SDL_CreateWindow("sdl2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  assert(self.window);
}

void cppes8::sdl2::shutdown(cppes8::sdl2::SDL2& self) {
  assert(self.window);
  SDL_DestroyWindow(self.window);
  SDL_Quit();
}

bool cppes8::sdl2::poll_event(cppes8::sdl2::SDL2& self, SDL_Event* ev) {
  assert(self.window);
  assert(ev);
  if (SDL_PollEvent(ev)) {
    if (ev->type == SDL_QUIT) {
      self.has_close_request = true;
    }
    return true;
  }
  return false;
}

HWND cppes8::sdl2::get_hwnd(cppes8::sdl2::SDL2& self) {
  assert(self.window);
  SDL_SysWMinfo si;
  SDL_VERSION(&si.version);
  SDL_bool b = SDL_GetWindowWMInfo(self.window, &si);
  assert(b == SDL_TRUE);
  assert(si.subsystem == SDL_SYSWM_WINDOWS);
  return si.info.win.window;
}

#endif // CPPES8_SRC_SDL2_HPP_INCLUDED
