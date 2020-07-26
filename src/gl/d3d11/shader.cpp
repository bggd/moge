#include "shader.hpp"

void moge::gl::createShaderD3D11(moge::gl::ContextD3D11& ctx, moge::gl::ShaderD3D11& shdr, moge::gl::ShaderDecl& decl) {
  MOGE_ASSERT(!shdr.input_layour_refptr);
  MOGE_ASSERT(!shdr.vs_id);
  MOGE_ASSERT(!shdr.ps_id);
  MOGE_ASSERT(!shdr.stride);

  MOGE_ASSERT(decl.inputArray);
  MOGE_ASSERT(decl.numInput);
  MOGE_ASSERT(decl.numInput <= MOGE_GL_INPUT_ELEMENT_MAX);
  MOGE_ASSERT(decl.vertexShader);
  MOGE_ASSERT(decl.pixelShader);
  MOGE_ASSERT(decl.numByteOfVertexShader);
  MOGE_ASSERT(decl.numByteOfPixelShader);

  D3D11_INPUT_ELEMENT_DESC descs[MOGE_GL_INPUT_ELEMENT_MAX];
  ZeroMemory(descs, sizeof(D3D11_INPUT_ELEMENT_DESC) * MOGE_GL_INPUT_ELEMENT_MAX);

  uint32_t offset = 0;
  for (uint32_t i = 0; i < decl.numInput; ++i) {
    MOGE_ASSERT(decl.inputArray[i].hlslSemanticName);
    MOGE_ASSERT(decl.inputArray[i].numFloat > 0);
    MOGE_ASSERT(decl.inputArray[i].numFloat < 5);

    D3D11_INPUT_ELEMENT_DESC& d = descs[i];
    d.SemanticName = decl.inputArray[i].hlslSemanticName;
    d.SemanticIndex = decl.inputArray[i].hlslSemanticIndex;
    d.AlignedByteOffset += offset;

    // clang-format off
    switch (decl.inputArray[i].numFloat) {
      case 1: d.Format = DXGI_FORMAT_R32_FLOAT; offset += 4; break;
      case 2: d.Format = DXGI_FORMAT_R32G32_FLOAT; offset += 8; break;
      case 3: d.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12; break;
      case 4: d.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; offset += 16; break;
      default: MOGE_ASSERT(!"moge::gl::ShaderDecl::InputLayout.numFloat must be 1..4"); break;
    }
    // clang-format on

    d.InputSlot = 0;
    d.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    d.InstanceDataStepRate = 0;
  }

  shdr.stride = offset;

  HRESULT hr;
  hr = ctx.d3d_device->CreateInputLayout(descs, decl.numInput, decl.vertexShader, decl.numByteOfVertexShader, &shdr.input_layour_refptr);
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreateVertexShader(decl.vertexShader, decl.numByteOfVertexShader, NULL, &shdr.vs_id);
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreatePixelShader(decl.pixelShader, decl.numByteOfPixelShader, NULL, &shdr.ps_id);
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
