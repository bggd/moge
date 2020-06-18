#include "vertex_buffer.hpp"

void moge::gl::createVertexBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::VertexBufferD3D11& vbo, uint32_t num_bytes) {
  MOGE_ASSERT(!vbo.buffer_id);

  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
  bd.ByteWidth = num_bytes;
  bd.Usage = D3D11_USAGE_DYNAMIC;
  bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  bd.MiscFlags = 0;
  bd.StructureByteStride = 0;

  HRESULT hr;
  hr = ctx.d3d_device->CreateBuffer(&bd, NULL, &vbo.buffer_id);
  MOGE_ASSERT(SUCCEEDED(hr));
}

void moge::gl::destroyVertexBufferD3D11(moge::gl::VertexBufferD3D11& vbo) {
  MOGE_ASSERT(vbo.buffer_id);
  vbo.buffer_id->Release();
  vbo.buffer_id = NULL;
}

void moge::gl::uploadVertexBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::VertexBufferD3D11& vbo, const void* vertices, size_t num_bytes) {
  MOGE_ASSERT(vbo.buffer_id);
  MOGE_ASSERT(vertices);

  D3D11_MAPPED_SUBRESOURCE mapped;
  ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

  HRESULT hr;
  hr = ctx.d3d_device_context->Map(vbo.buffer_id, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
  MOGE_ASSERT(SUCCEEDED(hr));
  memcpy(mapped.pData, vertices, num_bytes);
  ctx.d3d_device_context->Unmap(vbo.buffer_id, 0);
}
