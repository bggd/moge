#include "gl.hpp"

void moge::gl::clearD3D11(moge::gl::ContextD3D11& ctx, float R, float G, float B, float A) {
  float color[4] = {R, G, B, A};
  ctx.d3d_device_context->ClearRenderTargetView(ctx.d3d_render_target_view, color);
}

void moge::gl::presentD3D11(moge::gl::ContextD3D11& ctx) {
  ctx.d3d_swap_chain->Present(1, 0);
}

void moge::gl::setShaderD3D11(ContextD3D11& ctx, ShaderD3D11& shdr) {
  ctx.d3d_device_context->VSSetShader(shdr.vs_id, NULL, 0);
  ctx.d3d_device_context->PSSetShader(shdr.ps_id, NULL, 0);
  ctx.d3d_device_context->IASetInputLayout(shdr.input_layour_refptr);
  for (uint32_t i = 0; i < MOGE_GL_VERTEX_BUFFER_SLOT_MAX; ++i) {
    ctx.stride_from_shader[i] = shdr.stride[i];
  }
}

void moge::gl::setConstantBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ConstantBufferD3D11& cb) {
  ID3D11Buffer* ary[2] = {cb.buffer_id, NULL};
  ctx.d3d_device_context->VSSetConstantBuffers(0, 1, ary);
}

void moge::gl::setTextureD3D11(moge::gl::ContextD3D11& ctx, moge::gl::TextureD3D11& tex) {
  ID3D11ShaderResourceView* srv_ary[2] = {tex.srv, NULL};
  ctx.d3d_device_context->PSSetShaderResources(0, 1, srv_ary);
}

void moge::gl::setVertexBufferD3D11(moge::gl::ContextD3D11& ctx, moge::gl::VertexBufferD3D11& vbo, uint8_t slot) {
  MOGE_ASSERT(slot < MOGE_GL_VERTEX_BUFFER_SLOT_MAX);
  MOGE_ASSERT(ctx.stride_from_shader[slot]);

  const UINT offset = 0;
  const UINT stride = sizeof(float) * ctx.stride_from_shader[slot];
  ctx.d3d_device_context->IASetVertexBuffers(slot, 1, &vbo.buffer_id, &stride, &offset);

  ctx.num_byte_of_vbo[slot] = vbo.num_bytes;
}

void moge::gl::drawD3D11(moge::gl::ContextD3D11& ctx, uint32_t count, uint16_t offset) {
  for (uint32_t i = 0; i < MOGE_GL_VERTEX_BUFFER_SLOT_MAX; ++i) {
    if (ctx.stride_from_shader[i]) {
      MOGE_ASSERT((count + offset) <= (sizeof(float) * ctx.num_byte_of_vbo[i]));
    }
  }
  ctx.d3d_device_context->Draw(count, offset);
}
