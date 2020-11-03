#include "gl.hpp"
#include "bind.hpp"

void moge::gl::clearOGL(moge::gl::ContextOGL&, float R, float G, float B, float A) {
  MOGE_GL_CHECK(glClearColor(R, G, B, A));
  MOGE_GL_CHECK(glClear(GL_COLOR_BUFFER_BIT));
}

void moge::gl::presentOGL(moge::gl::ContextOGL&) {
}

void moge::gl::setShaderOGL(moge::gl::ContextOGL&, moge::gl::ShaderOGL& shdr) {
  MOGE_ASSERT(shdr.id);

  uint32_t index = 0;
  for (uint32_t i = 0; i < shdr.numInput; ++i) {
    GLuint loc = shdr.inputArray[i].glslAttributeLocation;
    GLint size = shdr.inputArray[i].numFloat;
    GLsizei stride = sizeof(GLfloat) * shdr.stride;
    MOGE_GL_CHECK(glEnableVertexAttribArray(loc));
    MOGE_GL_CHECK(glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)(sizeof(GLfloat) * index)));
    index += size;
  }

  MOGE_GL_CHECK(glUseProgram(shdr.id));
}

void moge::gl::setUniformArrayOGL(moge::gl::ContextOGL&, moge::gl::UniformArrayOGL&) {
}

void moge::gl::setTextureOGL(moge::gl::ContextOGL&, moge::gl::TextureOGL& tex) {
  MOGE_ASSERT(tex.id);

  MOGE_GL_CHECK(glBindTexture(GL_TEXTURE_2D, tex.id));
}

void moge::gl::setVertexBufferOGL(moge::gl::ContextOGL&, moge::gl::VertexBufferOGL& vbo) {
  MOGE_ASSERT(vbo.id);
  MOGE_ASSERT(vbo.num_bytes);

  MOGE_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo.id));
}

void moge::gl::drawOGL(moge::gl::ContextOGL&, enum MOGE_GL_DRAW_PRIMITIVE topology, uint32_t count, uint16_t offset) {
  MOGE_ASSERT(topology);

  static const GLenum _topologies[2] = {
      0, GL_TRIANGLES};

  GLenum primitive = _topologies[topology];

  MOGE_GL_CHECK(glDrawArrays(primitive, offset, count));
}
