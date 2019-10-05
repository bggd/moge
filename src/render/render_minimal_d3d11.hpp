#ifndef MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED
#define MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED

#include "d3d11.hpp"
#include "vertex_buffer_d3d11.hpp"

#define MOGE_RENDER_MINIMAL_VB_ARARY_NUM 2
#define MOGE_RENDER_MINIMAL_VB_BYTES 2048

namespace moge {

struct RenderMiniMalD3D11 {

  moge::D3D11 d3d11;
  moge::VertexBufferD3D11 vb[MOGE_RENDER_MINIMAL_VB_ARARY_NUM];

  void create(HWND hwnd) {
    this->d3d11.init_d3d11(hwnd);
    for (auto& i : vb) {
      i.create(this->d3d11, MOGE_RENDER_MINIMAL_VB_BYTES);
    }
  }

  void destroy() {
    for (auto& i : vb) {
      i.destroy();
    }
    this->d3d11.deinit_d3d11();
  }

}; // struct RenderMiniMalD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED
