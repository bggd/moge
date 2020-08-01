#include "uniform_array.hpp"
#include "shader.hpp"

void moge::gl::createUniformArrayD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ShaderD3D11&, moge::gl::UniformArrayD3D11& cb, UniformArrayDesc& desc) {
  MOGE_ASSERT(!cb.buffer_id);
  MOGE_ASSERT(!cb.shader_stage);
  MOGE_ASSERT(!cb.num_element);
  MOGE_ASSERT(desc.stage);
  MOGE_ASSERT(desc.type == MOGE_GL_UNIFORM_ARRAY_TYPE_FLOAT4);
  MOGE_ASSERT(desc.numElement);

  UINT bytewidth = sizeof(float) * desc.numElement;
  if (bytewidth < 16) {
    bytewidth += 16 - bytewidth;
  }
  else {
    bytewidth += bytewidth % 16;
  }
  MOGE_ASSERT(bytewidth <= UINT16_MAX);

  D3D11_BUFFER_DESC cbd;
  ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
  cbd.ByteWidth = bytewidth;
  cbd.Usage = D3D11_USAGE_DYNAMIC;
  cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
  cbd.MiscFlags = 0;
  cbd.StructureByteStride = 0;

  HRESULT hr;
  hr = ctx.d3d_device->CreateBuffer(&cbd, NULL, &cb.buffer_id);
  MOGE_ASSERT(SUCCEEDED(hr));

  cb.shader_stage = desc.stage;
  cb.num_element = desc.numElement;
}

void moge::gl::destroyUniformArrayD3D11(moge::gl::UniformArrayD3D11& cb) {
  MOGE_ASSERT(cb.buffer_id);
  MOGE_ASSERT(cb.shader_stage);
  MOGE_ASSERT(cb.num_element);

  cb.buffer_id->Release();
  cb.buffer_id = NULL;
  cb.shader_stage = MOGE_GL_SHADER_STAGE_UNDEFINED;
  cb.num_element = 0;
}

void moge::gl::uploadUniformArrayD3D11(moge::gl::ContextD3D11& ctx, moge::gl::UniformArrayD3D11& cb, const void* data, size_t num_bytes) {
  MOGE_ASSERT(cb.buffer_id);
  MOGE_ASSERT(cb.shader_stage);
  MOGE_ASSERT(cb.num_element);
  MOGE_ASSERT(num_bytes == (sizeof(float) * cb.num_element));

  D3D11_MAPPED_SUBRESOURCE mapped;
  ZeroMemory(&mapped, sizeof(D3D11_MAPPED_SUBRESOURCE));

  HRESULT hr;
  hr = ctx.d3d_device_context->Map(cb.buffer_id, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
  MOGE_ASSERT(SUCCEEDED(hr));
  memcpy(mapped.pData, data, sizeof(float) * cb.num_element);
  ctx.d3d_device_context->Unmap(cb.buffer_id, 0);
}
