#ifndef MOGE_SRC_GL_D3D11_TEXTURE_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_TEXTURE_HPP_INCLUDED

#include "context.hpp"
#include "../gl.hpp"

namespace moge {
namespace gl {

struct TextureD3D11 {
  ID3D11Texture2D* texture_id;
  ID3D11ShaderResourceView* srv;
};

void createTextureD3D11(ContextD3D11& ctx, TextureD3D11& tex, TextureDecl& decl);
void destroyTextureD3D11(TextureD3D11& tex);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_TEXTURE_HPP_INCLUDED
