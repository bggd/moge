#include "vertex_buffer.hpp"
#include "bind.hpp"

void moge::gl::createVertexBufferOGL(moge::gl::ContextOGL&, moge::gl::VertexBufferOGL& vbo, uint32_t num_bytes) {
  MOGE_ASSERT(!vbo.id);
  MOGE_ASSERT(!vbo.num_bytes);
  MOGE_ASSERT(num_bytes);

  GLuint id;
  MOGE_GL_CHECK(glGenBuffers(1, &id));
  MOGE_ASSERT(id);
  MOGE_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, id));

  bool ok;
  MOGE_GL_CHECK(ok = glIsBuffer(id));
  MOGE_ASSERT(ok);

  vbo.id = id;
  vbo.num_bytes = num_bytes;
}

void moge::gl::destroyVertexBufferOGL(moge::gl::ContextOGL&, moge::gl::VertexBufferOGL& vbo) {
  MOGE_ASSERT(vbo.id);
  MOGE_ASSERT(vbo.num_bytes);

  bool ok;
  MOGE_GL_CHECK(ok = glIsBuffer(vbo.id));
  MOGE_ASSERT(ok);

  MOGE_GL_CHECK(glDeleteBuffers(1, &vbo.id));

  vbo.id = 0;
  vbo.num_bytes = 0;
}

void moge::gl::uploadVertexBufferOGL(moge::gl::ContextOGL&, moge::gl::VertexBufferOGL& vbo, const void* vertices, size_t num_bytes) {
  MOGE_ASSERT(vbo.id);
  MOGE_ASSERT(vbo.num_bytes);
  MOGE_ASSERT(vertices);
  MOGE_ASSERT(num_bytes);
  MOGE_ASSERT(num_bytes == vbo.num_bytes);

  bool ok;
  MOGE_GL_CHECK(ok = glIsBuffer(vbo.id));
  MOGE_ASSERT(ok);

  MOGE_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, num_bytes, vertices, GL_DYNAMIC_DRAW));
}
