#ifndef MOGE_SRC_GL_OGL_VERTEX_BUFFER_HPP_INCLUDED
#define MOGE_SRC_GL_OGL_VERTEX_BUFFER_HPP_INCLUDED

#include "context.hpp"
#include "../../trivial.hpp"
#include <stdint.h>

namespace moge {
namespace gl {

struct VertexBufferOGL {
  uint32_t id;
  uint32_t num_bytes;
};

void createVertexBufferOGL(ContextOGL& ctx, VertexBufferOGL& vbo, uint32_t num_bytes);
void destroyVertexBufferOGL(VertexBufferOGL& vbo);
void uploadVertexBufferOGL(ContextOGL& ctx, VertexBufferOGL& vbo, const void* vertices, size_t num_bytes);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_OGL_VERTEX_BUFFER_HPP_INCLUDED
