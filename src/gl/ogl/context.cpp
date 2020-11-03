#include "context.hpp"

#include "bind.hpp"

void moge::gl::createContextOGL(moge::gl::ContextOGL& ctx) {
  MOGE_ASSERT(!ctx.VAO);

  GLuint VAO;
  MOGE_GL_CHECK(glGenVertexArrays(1, &VAO));
  MOGE_GL_CHECK(glBindVertexArray(VAO));
  ctx.VAO = VAO;
}

void moge::gl::destroyContextOGL(moge::gl::ContextOGL& ctx) {
  MOGE_ASSERT(ctx.VAO);
}

void moge::gl::resizeBackBufferOGL(ContextOGL&) {
}
