#ifndef CPPES8_SRC_CPPES8_HPP_INCLUDED
#define CPPES8_SRC_CPPES8_HPP_INCLUDED

#include "../../src/render/render_minimal_d3d11.hpp"
#include "handle.hpp"
#include "sdl2.hpp"
#include "shader.hpp"

#define CPPES8_CONFIG_MAX_VERTICES 49512
#define CPPES8_CONFIG_MAX_SHADERS 8

namespace cppes8 {

struct CPPES8 {

  struct StateGfx {
    cppes8::shader::ShaderHandle current_shader_handle;
  };

  cppes8::sdl2::SDL2 sdl2;
  moge::RenderMiniMalD3D11 render;
  cppes8::handle::HandlePool<cppes8::shader::Shader, CPPES8_CONFIG_MAX_SHADERS> shaders;
  StateGfx state_gfx;
};

void init(CPPES8& self);
void shutdown(CPPES8& self);
void run(CPPES8& self, void (*on_step)(void));

} // namespace cppes8

#include "gfx.hpp"

void cppes8::init(cppes8::CPPES8& self) {
  cppes8::sdl2::init(self.sdl2);
  self.render.create(cppes8::sdl2::get_hwnd(self.sdl2), CPPES8_CONFIG_MAX_VERTICES);
}

void cppes8::shutdown(cppes8::CPPES8& self) {
  self.render.destroy();
  cppes8::sdl2::shutdown(self.sdl2);
}

void cppes8::run(cppes8::CPPES8& self, void (*on_step)(void)) {
  assert(on_step);

  auto frame = [&self, &on_step](void*) {
    SDL_Event ev;
    while (cppes8::sdl2::poll_event(self.sdl2, &ev)) {}
    if (self.sdl2.has_close_request) {
      exit(0);
    }
    on_step();
  };

  for (;;) {
    frame(nullptr);
    SDL_Delay(20);
  }
}

#endif // CPPES8_SRC_CPPES8_HPP_INCLUDED
