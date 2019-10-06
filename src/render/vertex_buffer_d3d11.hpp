#ifndef MOGE_SRC_RENDER_VERTEX_BUFFER_D3D11_HPP_INCLUDED
#define MOGE_SRC_RENDER_VERTEX_BUFFER_D3D11_HPP_INCLUDED

#include "d3d11.hpp"
#include <stdint.h>

namespace moge {

struct VertexBufferD3D11 {

  ID3D11Buffer* buffer = nullptr;

  void create(moge::D3D11& d3d11, size_t num_bytes) {
    assert(this->buffer == nullptr);

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = num_bytes;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags = 0;
    desc.StructureByteStride = 0;

    HRESULT hr;
    hr = d3d11.d3d_device->CreateBuffer(&desc, NULL, &this->buffer);
    assert(SUCCEEDED(hr));
    assert(this->buffer);
  }

  void destroy() {
    assert(this->buffer);
    this->buffer->Release();
  }

  void upload(moge::D3D11& d3d11, const void* vertices, size_t num_bytes) {
    assert(this->buffer);
    assert(vertices);

    D3D11_MAPPED_SUBRESOURCE mapped;
    ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

    HRESULT hr;
    hr = d3d11.d3d_device_context->Map(this->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    assert(SUCCEEDED(hr));
    memcpy(mapped.pData, vertices, num_bytes);
    d3d11.d3d_device_context->Unmap(this->buffer, 0);
  }

}; // struct VertexBufferD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_VERTEX_BUFFER_D3D11_HPP_INCLUDED
