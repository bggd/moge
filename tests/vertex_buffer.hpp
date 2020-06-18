#include <gtest/gtest.h>

#include "gl_context_fixture.hpp"
#include "../src/gl/d3d11/vertex_buffer.hpp"

TEST_F(MogeGLContextFixture, MogeVertexBufer) {
  moge::gl::VertexBufferD3D11 ctx = {};
  moge::gl::createVertexBufferD3D11(gl_ctx, ctx, sizeof(float) * 8);
  float vertices[8] = {};
  moge::gl::uploadVertexBufferD3D11(gl_ctx, ctx, vertices, sizeof(float) * 8);
  moge::gl::destroyVertexBufferD3D11(ctx);
}
