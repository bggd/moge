#ifndef MOGE_TEST_GL_CONTEXT_FIXTURE_HPP_INCLUDED
#define MOGE_TEST_GL_CONTEXT_FIXTURE_HPP_INCLUDED

#include "sdl_fixture.hpp"
#include "../src/gl/d3d11/context.hpp"

struct MogeGLContextFixture : MogeSDLFixture {
  moge::gl::ContextD3D11 gl_ctx;

  virtual void SetUp() override {
    MogeSDLFixture::SetUp();
    moge::gl::ContextD3D11 ctx = {};
    gl_ctx = ctx;
    gl_ctx.hwnd = MogeSDLFixture::getHWND();
    moge::gl::createContextD3D11(gl_ctx);
  }

  virtual void TearDown() override {
    moge::gl::destroyContextD3D11(gl_ctx);
    MogeSDLFixture::TearDown();
  }
};

#endif // MOGE_TEST_GL_CONTEXT_FIXTURE_HPP_INCLUDED
