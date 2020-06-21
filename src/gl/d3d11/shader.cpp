#include "shader.hpp"

void moge::gl::createShaderD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ShaderD3D11& shdr, moge::gl::ShaderDecl& decl) {
  MOGE_ASSERT(!shdr.input_layour_refptr);
  MOGE_ASSERT(!shdr.vs_id);
  MOGE_ASSERT(!shdr.ps_id);
  MOGE_ASSERT(!shdr.stride);

  MOGE_ASSERT(decl.input_ary);
  MOGE_ASSERT(decl.num_input);
  MOGE_ASSERT(decl.num_input <= MOGE_GL_INPUT_ELEMENT_MAX);
  MOGE_ASSERT(decl.vertex_shader);
  MOGE_ASSERT(decl.pixel_shader);
  MOGE_ASSERT(decl.num_byte_of_vertex_shader);
  MOGE_ASSERT(decl.num_byte_of_pixel_shader);

  D3D11_INPUT_ELEMENT_DESC descs[MOGE_GL_INPUT_ELEMENT_MAX];
  ZeroMemory(descs, sizeof(D3D11_INPUT_ELEMENT_DESC) * MOGE_GL_INPUT_ELEMENT_MAX);

  uint32_t offset = 0;
  for (uint32_t i = 0; i < decl.num_input; ++i) {
    MOGE_ASSERT(decl.input_ary[i].semantic_name);
    MOGE_ASSERT(decl.input_ary[i].num_float > 0);
    MOGE_ASSERT(decl.input_ary[i].num_float < 5);

    D3D11_INPUT_ELEMENT_DESC& d = descs[i];
    d.SemanticName = decl.input_ary[i].semantic_name;
    d.SemanticIndex = decl.input_ary[i].semantic_index;
    d.AlignedByteOffset += offset;

    // clang-format off
    switch (decl.input_ary[i].num_float) {
      case 1: d.Format = DXGI_FORMAT_R32_FLOAT; offset += 4; break;
      case 2: d.Format = DXGI_FORMAT_R32G32_FLOAT; offset += 8; break;
      case 3: d.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12; break;
      case 4: d.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; offset += 16; break;
      default: MOGE_ASSERT(!"moge::gl::ShaderDecl::InputLayout.num_float must be 1..4"); break;
    }
    // clang-format on

    d.InputSlot = 0;
    d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    d.InstanceDataStepRate = 0;
  }

  shdr.stride = offset;

  HRESULT hr;
  hr = ctx.d3d_device->CreateInputLayout(descs, decl.num_input, decl.vertex_shader, decl.num_byte_of_vertex_shader, &shdr.input_layour_refptr);
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreateVertexShader(decl.vertex_shader, decl.num_byte_of_vertex_shader, NULL, &shdr.vs_id);
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreatePixelShader(decl.pixel_shader, decl.num_byte_of_pixel_shader, NULL, &shdr.ps_id);
  MOGE_ASSERT(SUCCEEDED(hr));
}

void moge::gl::destroyShaderD3D11(moge::gl::ShaderD3D11& shdr) {
  MOGE_ASSERT(shdr.input_layour_refptr);
  MOGE_ASSERT(shdr.vs_id);
  MOGE_ASSERT(shdr.ps_id);
  MOGE_ASSERT(shdr.stride);

  shdr.input_layour_refptr->Release();
  shdr.vs_id->Release();
  shdr.ps_id->Release();

  shdr.input_layour_refptr = NULL;
  shdr.vs_id = NULL;
  shdr.ps_id = NULL;
  shdr.stride = 0;
}
