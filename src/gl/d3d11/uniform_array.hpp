#ifndef MOGE_SRC_GL_D3D11_UNIFORM_ARRAY_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_UNIFORM_ARRAY_HPP_INCLUDED

#include "context.hpp"
#include "../gl.hpp"

namespace moge {
namespace gl {

struct UniformArrayD3D11 {
  ID3D11Buffer* buffer_id;
  enum MOGE_GL_SHADER_STAGE shader_stage;
  uint32_t num_element;
};

void createUniformArrayD3D11(ContextD3D11& ctx, UniformArrayD3D11& cb, UniformArrayDecl& decl);
void destroyUniformArrayD3D11(UniformArrayD3D11& cb);
void uploadUniformArrayD3D11(ContextD3D11& ctx, UniformArrayD3D11& cb, const void* data, size_t num_bytes);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_CONSTANT_BUFFER_HPP_INCLUDED
