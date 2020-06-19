#include <gtest/gtest.h>

#include "gl_context_fixture.hpp"
#include "../src/gl/d3d11/texture.hpp"

TEST_F(MogeGLContextFixture, MogeGLTexture) {
  moge::gl::TextureD3D11 tex = {};
  const uint32_t width = 8;
  const uint32_t height = 8;
  uint8_t rgba[width * height * 4];
  moge::gl::createTextureD3D11(gl_ctx, tex, rgba, width, height);
  moge::gl::destroyTextureD3D11(tex);
}
