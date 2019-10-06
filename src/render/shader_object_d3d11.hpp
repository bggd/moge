#ifndef MOGE_SRC_RENDER_SHADER_OBJECT_D3D11_HPP_INCLUDED
#define MOGE_SRC_RENDER_SHADER_OBJECT_D3D11_HPP_INCLUDED

#include "d3d11.hpp"

namespace moge {

struct ShaderObjectD3D11 {

  enum class Type {
    NONE,
    VERTEX_SHADER,
    PIXEL_SHADER
  };

  ID3D11VertexShader* vs = nullptr;
  ID3D11PixelShader* ps = nullptr;
  ShaderObjectD3D11::Type type = ShaderObjectD3D11::Type::NONE;

  void
  create(moge::D3D11& d3d11, const void* code, size_t num_bytes, ShaderObjectD3D11::Type shader_type) {
    assert(this->vs == nullptr && this->ps == nullptr && this->type == ShaderObjectD3D11::Type::NONE);
    assert(shader_type != ShaderObjectD3D11::Type::NONE);
    assert(shader_type == ShaderObjectD3D11::Type::VERTEX_SHADER || shader_type == ShaderObjectD3D11::Type::PIXEL_SHADER);

    HRESULT hr;
    if (shader_type == ShaderObjectD3D11::Type::VERTEX_SHADER) {
      hr = d3d11.d3d_device->CreateVertexShader(code, num_bytes, NULL, &this->vs);
    }
    else if (shader_type == ShaderObjectD3D11::Type::PIXEL_SHADER) {
      hr = d3d11.d3d_device->CreatePixelShader(code, num_bytes, NULL, &this->ps);
    }
    assert(SUCCEEDED(hr));
  }

  void destroy() {
    assert(this->type != ShaderObjectD3D11::Type::NONE);
    assert(this->type == ShaderObjectD3D11::Type::VERTEX_SHADER || this->type == ShaderObjectD3D11::Type::PIXEL_SHADER);

    if (this->type == ShaderObjectD3D11::Type::VERTEX_SHADER) {
      assert(this->vs && this->ps == nullptr);
      this->vs->Release();
    }
    else {
      assert(this->ps && this->vs == nullptr);
      this->ps->Release();
    }
  }

}; // struct ShaderObjectD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_SHADER_OBJECT_D3D11_HPP_INCLUDED
