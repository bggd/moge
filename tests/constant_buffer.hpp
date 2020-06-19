#include <gtest/gtest.h>

#include "gl_context_fixture.hpp"
#include "../src/gl/d3d11/constant_buffer.hpp"

TEST_F(MogeGLContextFixture, MogeGLConstantBuffer) {
  moge::gl::ConstantBufferD3D11 cb = {};
  float data[8];
  moge::gl::createConstantBufferD3D11(gl_ctx, cb, 8);
  moge::gl::uploadConstantBufferD3D11(gl_ctx, cb, data, 8);
  moge::gl::destroyConstantBufferD3D11(cb);
}
