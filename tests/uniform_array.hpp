#include <gtest/gtest.h>

#include "gl_context_fixture.hpp"
#include "../src/gl/d3d11/uniform_array.hpp"

TEST_F(MogeGLContextFixture, MogeGLUniformArray) {
  moge::gl::UniformArrayD3D11 cb = {};
  float data[8];
  moge::gl::createUniformArrayD3D11(gl_ctx, cb, MOGE_GL_SHADER_STAGE_VERTEX, 8);
  moge::gl::uploadUniformArrayD3D11(gl_ctx, cb, data, 8);
  moge::gl::destroyUniformArrayD3D11(cb);
}
