#ifndef MOGE_SRC_GL_D3D11_VERTEX_BUFFER_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_VERTEX_BUFFER_HPP_INCLUDED

#include "context.hpp"
#include "../../trivial.hpp"

namespace moge {
namespace gl {

struct VertexBufferD3D11 {
  ID3D11Buffer* buffer_id;
  uint32_t num_bytes;
};

void createVertexBufferD3D11(ContextD3D11& ctx, VertexBufferD3D11& vbo, uint32_t num_bytes);
void destroyVertexBufferD3D11(VertexBufferD3D11& vbo);
void uploadVertexBufferD3D11(ContextD3D11& ctx, VertexBufferD3D11& vbo, const void* vertices, size_t num_bytes);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_VERTEX_BUFFER_HPP_INCLUDED
