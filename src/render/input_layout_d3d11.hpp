#ifndef MOGE_SRC_RENDER_INPUT_LAYOUT_D3D11_HPP_INCLUDED
#define MOGE_SRC_RENDER_INPUT_LAYOUT_D3D11_HPP_INCLUDED

#include "d3d11.hpp"
#include <stdint.h>

namespace moge {

struct InputLayoutD3D11 {

  ID3D11InputLayout* input_layout = nullptr;

  void create(moge::D3D11& d3d11, const D3D11_INPUT_ELEMENT_DESC* descs, uint32_t num_desc, const void* bytecode, size_t num_bytes) {
    assert(this->input_layout == nullptr);
    assert(descs);
    assert(bytecode);
    HRESULT hr;
    hr = d3d11.d3d_device->CreateInputLayout(descs, num_desc, bytecode, num_bytes, &this->input_layout);
    assert(SUCCEEDED(hr));
  }

  void destroy() {
    assert(this->input_layout);
    this->input_layout->Release();
  }

}; // struct InputLayoutD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_INPUT_LAYOUT_D3D11_HPP_INCLUDED
