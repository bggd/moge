#ifndef MOGE_SRC_GL_D3D11_SHADER_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_SHADER_HPP_INCLUDED

#include "../gl.hpp"
#include "context.hpp"

namespace moge {
namespace gl {

struct ShaderD3D11 {
  ID3D11InputLayout* input_layour_refptr;
  ID3D11VertexShader* vs_id;
  ID3D11PixelShader* ps_id;
  uint32_t stride[MOGE_GL_VERTEX_BUFFER_SLOT_MAX];
};

void createShaderD3D11(ContextD3D11& ctx, ShaderD3D11& shdr, ShaderDecl& decl);
void destroyShaderD3D11(ShaderD3D11& shdr);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_SHADER_HPP_INCLUDED
