#ifndef MOGE_SRC_RENDER_TEXTURE2D_STATIC_D3D11_HPP_INCLUDED
#define MOGE_SRC_RENDER_TEXTURE2D_STATIC_D3D11_HPP_INCLUDED

#include "d3d11.hpp"
#include <stdint.h>

namespace moge {

struct Texture2DStaticD3D11 {

  ID3D11Texture2D* texture = nullptr;
  ID3D11ShaderResourceView* srv = nullptr;

  void create(moge::D3D11& d3d11, const void* rgba, uint32_t width, uint32_t height) {
    assert(this->texture == nullptr);
    assert(this->srv == nullptr);

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA init_data;
    ZeroMemory(&init_data, sizeof(D3D11_SUBRESOURCE_DATA));
    init_data.pSysMem = rgba;
    init_data.SysMemPitch = width * 4;
    init_data.SysMemSlicePitch = width * height * 4;

    D3D11_SUBRESOURCE_DATA ary[2];
    ZeroMemory(&ary, sizeof(D3D11_SUBRESOURCE_DATA) * 2);
    ary[0] = init_data;

    HRESULT hr;
    hr = d3d11.d3d_device->CreateTexture2D(&desc, ary, &this->texture);
    assert(SUCCEEDED(hr));

    D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
    ZeroMemory(&srv_desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    srv_desc.Format = desc.Format;
    srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srv_desc.Texture2D.MipLevels = desc.MipLevels;

    hr = d3d11.d3d_device->CreateShaderResourceView(this->texture, &srv_desc, &this->srv);
    assert(SUCCEEDED(hr));
  }

  void destroy() {
    assert(this->texture);
    assert(this->srv);
    this->texture->Release();
    this->srv->Release();
  }
}; // struct Texture2DStaticD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_TEXTURE2D_STATIC_D3D11_HPP_INCLUDED
