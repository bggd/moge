#ifndef MOGE_SRC_GL_OGL_UNIFORM_ARRAY_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_UNIFORM_ARRAY_HPP_INCLUDED

#include "context.hpp"
#include "shader.hpp"
#include "../gl.hpp"

namespace moge {
namespace gl {

struct UniformArrayOGL {
  int32_t loc;
  uint32_t num_element;
  enum MOGE_GL_UNIFORM_ARRAY_TYPE type;
};

void createUniformArrayOGL(ContextOGL& ctx, ShaderOGL& shdr, UniformArrayOGL& cb, UniformArrayDecl& decl);
void destroyUniformArrayOGL(UniformArrayOGL& cb);
void uploadUniformArrayOGL(ContextOGL& ctx, UniformArrayOGL& cb, const void* data, size_t num_bytes);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_OGL_UNIFORM_ARRAY_HPP_INCLUDED
