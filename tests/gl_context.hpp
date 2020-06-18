#include <gtest/gtest.h>

#include "sdl_fixture.hpp"
#include "../src/gl/d3d11/context.hpp"

TEST_F(MogeSDLFixture, MogeGLContext) {
  moge::gl::ContextD3D11 ctx = {};
  ctx.hwnd = getHWND();
  moge::gl::createContextD3D11(ctx);
  moge::gl::destroyContextD3D11(ctx);
}
