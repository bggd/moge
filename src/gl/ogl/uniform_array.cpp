#include "uniform_array.hpp"

#include "bind.hpp"
#include <stdint.h>

void moge::gl::createUniformArrayOGL(moge::gl::ContextOGL&, moge::gl::ShaderOGL& shdr, moge::gl::UniformArrayOGL& cb, UniformArrayDesc& desc) {
  MOGE_ASSERT(!cb.loc);
  MOGE_ASSERT(!cb.num_element);
  MOGE_ASSERT(!cb.type);
  MOGE_ASSERT(desc.name);
  MOGE_ASSERT(desc.type == MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4);
  MOGE_ASSERT(desc.numElement);
  MOGE_ASSERT((desc.numElement * sizeof(float)) <= UINT16_MAX);
  MOGE_ASSERT(((desc.numElement * sizeof(float)) % 4) == 0);

  GLint loc;
  MOGE_GL_CHECK(loc = glGetUniformLocation(shdr.id, desc.name));
  MOGE_ASSERT(loc > 0);

  cb.loc = loc;
  cb.num_element = desc.numElement;
  cb.type = desc.type;
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
