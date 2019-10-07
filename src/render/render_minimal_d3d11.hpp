#ifndef MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED
#define MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED

#include "C:/Program Files (x86)/Windows Kits/10/Include/10.0.17763.0/um/d3d11.h"
#include "d3d11.hpp"
#include "input_layout_d3d11.hpp"
#include "shader_object_d3d11.hpp"
#include "texture2d_static_d3d11.hpp"
#include "vertex_buffer_d3d11.hpp"

#define MOGE_RENDER_MINIMAL_VB_ARARY_NUM 2

namespace moge {

struct RenderMinimalInputLayoutD3D11 {
  const char* sem_name = nullptr;
  uint32_t sem_index = 0;
  uint32_t num_float = 0;
};

struct RenderMiniMalD3D11 {

  moge::D3D11 d3d11;
  ID3D11SamplerState* sampler_nearest = nullptr;
  moge::VertexBufferD3D11 vb[MOGE_RENDER_MINIMAL_VB_ARARY_NUM];
  size_t vb_num_bytes = 0;
  uint32_t vb_idx = 0;

  void create(HWND hwnd, uint32_t vertex_buffer_numb_bytes) {
    assert(this->sampler_nearest == nullptr);

    this->d3d11.init_d3d11(hwnd);

    for (auto& i : vb) {
      i.create(this->d3d11, vertex_buffer_numb_bytes);
    }
    this->vb_num_bytes = vertex_buffer_numb_bytes;

    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    desc.AddressU = desc.AddressV = desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.MaxAnisotropy = 1;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr;
    hr = this->d3d11.d3d_device->CreateSamplerState(&desc, &this->sampler_nearest);
    assert(SUCCEEDED(hr));
  }

  void destroy() {
    assert(this->sampler_nearest);
    this->sampler_nearest->Release();
    for (auto& i : vb) {
      i.destroy();
    }
    this->d3d11.deinit_d3d11();
  }

  moge::ShaderObjectD3D11 create_vertex_shader(const void* bytecode, size_t num_bytes) {
    moge::ShaderObjectD3D11 so;
    so.create(this->d3d11, bytecode, num_bytes, moge::ShaderObjectD3D11::Type::VERTEX_SHADER);
    return so;
  }

  moge::ShaderObjectD3D11 create_pixel_shader(const void* bytecode, size_t num_bytes) {
    moge::ShaderObjectD3D11 so;
    so.create(this->d3d11, bytecode, num_bytes, moge::ShaderObjectD3D11::Type::PIXEL_SHADER);
    return so;
  }

  moge::Texture2DStaticD3D11 create_texture2d_static(const void* pixels, uint32_t width, uint32_t height) {
    moge::Texture2DStaticD3D11 tex;
    tex.create(this->d3d11, pixels, width, height);
    return tex;
  }

  moge::InputLayoutD3D11 create_input_layout(const RenderMinimalInputLayoutD3D11* layouts, uint8_t num_layouts, const void* bytecode, size_t num_bytes) {
    assert(num_layouts <= 8);
    D3D11_INPUT_ELEMENT_DESC descs[8];
    ZeroMemory(descs, sizeof(D3D11_INPUT_ELEMENT_DESC) * 8);

    uint32_t offset = 0;
    for (int i = 0; i < num_layouts; ++i) {
      assert(layouts[i].sem_name);
      assert(layouts[i].num_float != 0 && layouts[i].num_float < 5);
      D3D11_INPUT_ELEMENT_DESC& d = descs[i];
      d.SemanticName = layouts[i].sem_name;
      d.SemanticIndex = layouts[i].sem_index;
      d.AlignedByteOffset = offset;
      switch (layouts[i].num_float) {
        case 1: d.Format = DXGI_FORMAT_R32_FLOAT; offset += 4; break;
        case 2: d.Format = DXGI_FORMAT_R32G32_FLOAT; offset += 8; break;
        case 3: d.Format = DXGI_FORMAT_R32G32B32_FLOAT; offset += 12; break;
        case 4: d.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; offset += 16; break;
        default: assert(!"input_layout.num_float must be 1..4"); break;
      }
      d.InputSlot = 0;
      d.InstanceDataStepRate = 0;
    }

    moge::InputLayoutD3D11 il;
    il.create(this->d3d11, descs, num_layouts, bytecode, num_bytes);
    return il;
  }

  void set_shader(const moge::ShaderObjectD3D11& vertex_shader, const moge::ShaderObjectD3D11& pixel_shader) {
    assert(vertex_shader.type == moge::ShaderObjectD3D11::Type::VERTEX_SHADER);
    assert(pixel_shader.type == moge::ShaderObjectD3D11::Type::PIXEL_SHADER);
    this->d3d11.d3d_device_context->VSSetShader(vertex_shader.vs, NULL, 0);
    this->d3d11.d3d_device_context->PSSetShader(pixel_shader.ps, NULL, 0);
  }

  void draw_triangles(const moge::Texture2DStaticD3D11& texture, const void* vertices, size_t num_bytes, uint32_t stride, const moge::InputLayoutD3D11& layout) {
    assert(vertices);
    assert(num_bytes > 0 && num_bytes <= this->vb_num_bytes);
    assert(stride > 0);

    this->vb_idx++;
    if (this->vb_idx >= MOGE_RENDER_MINIMAL_VB_ARARY_NUM) { this->vb_idx = 0; }

    this->vb[this->vb_idx].upload(this->d3d11, vertices, num_bytes);

    ID3D11Buffer* buffer = this->vb[this->vb_idx].buffer;
    UINT offset = 0;
    this->d3d11.d3d_device_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    this->d3d11.d3d_device_context->IASetInputLayout(layout.input_layout);
    ID3D11ShaderResourceView* ary_srv[2] = {texture.srv, NULL};
    this->d3d11.d3d_device_context->PSSetShaderResources(0, 1, ary_srv);
    ID3D11SamplerState* ary_sampler[2] = {this->sampler_nearest, NULL};
    this->d3d11.d3d_device_context->PSSetSamplers(0, 1, ary_sampler);
    this->d3d11.d3d_device_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->d3d11.d3d_device_context->Draw(num_bytes/stride, 0);
  }

}; // struct RenderMiniMalD3D11

} // namespace moge

#endif // MOGE_SRC_RENDER_RENDER_MINIMAL_HPP_INCLUDED
