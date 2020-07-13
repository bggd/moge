#ifndef MOGE_SRC_GL_OGL_GL_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_GL_HPP_INCLUDED

#include "context.hpp"
#include "shader.hpp"
#include "uniform_array.hpp"
#include "texture.hpp"
#include "vertex_buffer.hpp"

namespace moge {
namespace gl {

void clearOGL(ContextOGL& ctx, float R, float G, float B, float A);
void presentOGL(ContextOGL& ctx);
void setShaderOGL(ContextOGL& ctx, ShaderOGL& shdr);
void setUniformArrayD3D11(ContextOGL& ctx, UniformArrayOGL& cb);
void setTextureOGL(ContextOGL& ctx, TextureOGL& tex);
void setVertexBufferOGL(ContextOGL& ctx, VertexBufferOGL& vbo);
void drawOGL(ContextOGL& ctx, enum MOGE_GL_DRAW_PRIMITIVE topology, uint32_t count, uint16_t offset);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_OGL_GL_HPP_INCLUDED
