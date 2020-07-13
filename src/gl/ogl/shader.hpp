#ifndef MOGE_SRC_GL_OGL_SHADER_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_SHADER_HPP_INCLUDED

#include "../gl.hpp"
#include "context.hpp"

namespace moge {
namespace gl {

struct ShaderOGL {
  uint32_t id;
};

void createShaderOGL(ContextOGL& ctx, ShaderOGL& shdr, ShaderDecl& decl);
void destroyShaderOGL(ShaderOGL& shdr);

} // namespace gl
} // namespace moge
#endif // MOGE_SRC_GL_OGL_SHADER_HPP_INCLUDED
