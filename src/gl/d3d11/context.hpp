#ifndef MOGE_SRC_GL_D3D11_CONTEXT_HPP_INCLUDED
#define MOGE_SRC_GL_D3D11_CONTEXT_HPP_INCLUDED

#include <d3d11.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "../../trivial.hpp"

namespace moge {
namespace gl {

struct ContextD3D11 {
  HWND hwnd;
  ID3D11Device* d3d_device;
  ID3D11DeviceContext* d3d_device_context;
  IDXGISwapChain* d3d_swap_chain;
  ID3D11RenderTargetView* d3d_render_target_view;

  uint32_t stride_from_shader;
};

void createContextD3D11(ContextD3D11& ctx);
void destroyContextD3D11(ContextD3D11& ctx);

} // namespace gl
} // namespace moge

#endif // MOGE_SRC_GL_D3D11_CONTEXT_HPP_INCLUDED
