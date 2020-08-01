#include "texture.hpp"

void moge::gl::createTextureD3D11(moge::gl::ContextD3D11& ctx, moge::gl::TextureD3D11& tex, moge::gl::TextureDesc& desc) {
  MOGE_ASSERT(!tex.texture_id);
  MOGE_ASSERT(!tex.srv);
  MOGE_ASSERT(desc.data);
  MOGE_ASSERT(desc.width);
  MOGE_ASSERT(desc.height);
  MOGE_ASSERT(desc.imageFormat);
  MOGE_ASSERT(desc.minFilter);
  MOGE_ASSERT(desc.magFilter);

  static const DXGI_FORMAT _Formats[2] = {
      DXGI_FORMAT_UNKNOWN, DXGI_FORMAT_R8G8B8A8_UNORM};
  DXGI_FORMAT fmt = _Formats[desc.imageFormat];

  D3D11_TEXTURE2D_DESC td;
  ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
  td.Width = desc.width;
  td.Height = desc.height;
  td.MipLevels = 1;
  td.ArraySize = 1;
  td.Format = fmt;
  td.SampleDesc.Count = 1;
  td.SampleDesc.Quality = 0;
  td.Usage = D3D11_USAGE_IMMUTABLE;
  td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  td.CPUAccessFlags = 0;
  td.MiscFlags = 0;

  D3D11_SUBRESOURCE_DATA init_data;
  ZeroMemory(&init_data, sizeof(D3D11_SUBRESOURCE_DATA));
  init_data.pSysMem = desc.data;
  init_data.SysMemPitch = desc.width * 4;
  init_data.SysMemSlicePitch = desc.width * desc.height * 4;

  D3D11_SUBRESOURCE_DATA ary[2];
  ZeroMemory(&ary, sizeof(D3D11_SUBRESOURCE_DATA) * 2);
  ary[0] = init_data;

  HRESULT hr;
  hr = ctx.d3d_device->CreateTexture2D(&td, ary, &tex.texture_id);
  MOGE_ASSERT(SUCCEEDED(hr));

  D3D11_SHADER_RESOURCE_VIEW_DESC sd;
  ZeroMemory(&sd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
  sd.Format = td.Format;
  sd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  sd.Texture2D.MipLevels = td.MipLevels;

  hr = ctx.d3d_device->CreateShaderResourceView(tex.texture_id, &sd, &tex.srv);
  MOGE_ASSERT(SUCCEEDED(hr));
}

void moge::gl::destroyTextureD3D11(moge::gl::TextureD3D11& tex) {
  MOGE_ASSERT(tex.texture_id);
  MOGE_ASSERT(tex.srv);

  tex.texture_id->Release();
  tex.srv->Release();

  tex.texture_id = NULL;
  tex.srv = NULL;
}
