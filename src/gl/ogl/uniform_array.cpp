#include "uniform_array.hpp"

#include "bind.hpp"
#include <stdint.h>

void moge::gl::createUniformArrayOGL(moge::gl::ContextOGL&, moge::gl::ShaderOGL& shdr, moge::gl::UniformArrayOGL& cb, UniformArrayDecl& decl) {
  MOGE_ASSERT(!cb.loc);
  MOGE_ASSERT(!cb.num_element);
  MOGE_ASSERT(!cb.type);
  MOGE_ASSERT(decl.name);
  MOGE_ASSERT(decl.type == MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4);
  MOGE_ASSERT(decl.num_element);
  MOGE_ASSERT((decl.num_element * sizeof(float)) <= UINT16_MAX);
  MOGE_ASSERT(((decl.num_element * sizeof(float)) % 4) == 0);

  GLint loc;
  MOGE_GL_CHECK(loc = glGetUniformLocation(shdr.id, decl.name));
  MOGE_ASSERT(loc > 0);

  cb.loc = loc;
  cb.num_element = decl.num_element;
  cb.type = decl.type;
}

void moge::gl::destroyUniformArrayOGL(moge::gl::UniformArrayOGL& cb) {
  MOGE_ASSERT(cb.loc);
  MOGE_ASSERT(cb.num_element);
  MOGE_ASSERT(cb.type == MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4);

  cb.loc = 0;
  cb.num_element = 0;
  cb.type = MOGE_GL_UNIFORM_ARRAY_TYPE_UNDEFINED;
}

void moge::gl::uploadUniformArrayOGL(moge::gl::ContextOGL&, moge::gl::UniformArrayOGL& cb, const void* data, size_t num_bytes) {
  MOGE_ASSERT(cb.loc);
  MOGE_ASSERT(cb.num_element);
  MOGE_ASSERT(cb.type == MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4);
  MOGE_ASSERT(data);
  MOGE_ASSERT(num_bytes);
  MOGE_ASSERT(num_bytes == sizeof(float) * cb.num_element);

  MOGE_GL_CHECK(glUniform4fv(cb.loc, cb.num_element, static_cast<const GLfloat*>(data)));
}
