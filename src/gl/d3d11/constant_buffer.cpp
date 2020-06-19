#include "constant_buffer.hpp"

void moge::gl::createConstantBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ConstantBufferD3D11& cb, uint32_t num_float) {
  MOGE_ASSERT(!cb.buffer_id);
  MOGE_ASSERT(num_float);

  D3D11_BUFFER_DESC cbd;
  ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
  cbd.ByteWidth = sizeof(float) * num_float;
  cbd.Usage = D3D11_USAGE_DYNAMIC;
  cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  cbd.MiscFlags = 0;
  cbd.StructureByteStride = 0;

  HRESULT hr;
  hr = ctx.d3d_device->CreateBuffer(&cbd, NULL, &cb.buffer_id);
  MOGE_ASSERT(SUCCEEDED(hr));
}

void moge::gl::destroyConstantBufferD3D11(moge::gl::ConstantBufferD3D11& cb) {
  MOGE_ASSERT(cb.buffer_id);
  cb.buffer_id->Release();
  cb.buffer_id = NULL;
}

void moge::gl::uploadConstantBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ConstantBufferD3D11& cb, float* data, uint32_t num_float) {
  MOGE_ASSERT(cb.buffer_id);

  D3D11_MAPPED_SUBRESOURCE mapped;
  ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

  HRESULT hr;
  hr = ctx.d3d_device_context->Map(cb.buffer_id, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
  MOGE_ASSERT(SUCCEEDED(hr));
  memcpy(mapped.pData, data, sizeof(float) * num_float);
  ctx.d3d_device_context->Unmap(cb.buffer_id, 0);
}
