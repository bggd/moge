#ifndef MOGE_SRC_GL_D3D11_CONSTANT_BUFFER_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_CONSTANT_BUFFER_HPP_INCLUDED

#include "context.hpp"
#include "../../trivial.hpp"

namespace moge {
namespace gl {

struct ConstantBufferD3D11 {
  ID3D11Buffer* buffer_id;
};

void createConstantBufferD3D11(ContextD3D11& ctx, ConstantBufferD3D11& cb, uint32_t num_float);
void destroyConstantBufferD3D11(ConstantBufferD3D11& cb);
void uploadConstantBufferD3D11(ContextD3D11& ctx, ConstantBufferD3D11& cb, float* data, uint32_t num_float);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_CONSTANT_BUFFER_HPP_INCLUDED
