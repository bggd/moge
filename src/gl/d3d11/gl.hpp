#ifndef MOGE_SRC_GL_D3D11_GL_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_GL_HPP_INCLUDED

#include "context.hpp"
#include "shader.hpp"
#include "constant_buffer.hpp"
#include "texture.hpp"
#include "vertex_buffer.hpp"

namespace moge {
namespace gl {

void clearD3D11(ContextD3D11& ctx, float R, float G, float B, float A);
void presentD3D11(ContextD3D11& ctx);
void setShaderD3D11(ContextD3D11& ctx, ShaderD3D11& shdr);
void setConstantBufferD3D11(ContextD3D11& ctx, ConstantBufferD3D11& cb);
void setTextureD3D11(ContextD3D11& ctx, TextureD3D11& tex);
void setVertexBufferD3D11(ContextD3D11& ctx, VertexBufferD3D11& vbo, uint8_t slot);
void drawD3D11(ContextD3D11& ctx, uint32_t count, uint16_t offset);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_GL_HPP_INCLUDED
