#ifndef MOGE_SRC_GL_OGL_TEXTURE_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_TEXTURE_HPP_INCLUDED

#include "context.hpp"
#include "../gl.hpp"

namespace moge {
namespace gl {

struct TextureOGL {
  uint32_t id;
};

void createTextureOGL(ContextOGL& ctx, TextureOGL& tex, TextureDesc& desc);
void destroyTextureOGL(TextureOGL& tex);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_OGL_TEXTURE_HPP_INCLUDED
