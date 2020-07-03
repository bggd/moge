#include "context.hpp"

#include "../../trivial.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "winmm.lib")

namespace moge {
namespace gl {
namespace detail {

void setDefaults(ContextD3D11& ctx) {
  D3D11_BLEND_DESC bd;
  ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
  bd.AlphaToCoverageEnable = FALSE;
  bd.IndependentBlendEnable = FALSE;

  D3D11_RENDER_TARGET_BLEND_DESC rtd;
  ZeroMemory(&rtd, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
  rtd.BlendEnable = TRUE;
  rtd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
  rtd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
  rtd.BlendOp = D3D11_BLEND_OP_ADD;
  rtd.SrcBlendAlpha = D3D11_BLEND_ONE;
  rtd.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
  rtd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
  rtd.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

  bd.RenderTarget[0] = rtd;

  ID3D11BlendState* blend_state = NULL;

  HRESULT hr;
  hr = ctx.d3d_device->CreateBlendState(&bd, &blend_state);
  MOGE_ASSERT(SUCCEEDED(hr));

  float factor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  ctx.d3d_device_context->OMSetBlendState(blend_state, factor, 0xffffffff);
  blend_state->Release();

  D3D11_RASTERIZER_DESC rd;
  ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
  rd.FillMode = D3D11_FILL_SOLID;
  rd.CullMode = D3D11_CULL_NONE;
  rd.FrontCounterClockwise = TRUE;
  rd.DepthClipEnable = TRUE;

  ID3D11RasterizerState* rasterizer_state = NULL;
  hr = ctx.d3d_device->CreateRasterizerState(&rd, &rasterizer_state);
  MOGE_ASSERT(SUCCEEDED(hr));
  rasterizer_state->Release();

  ctx.d3d_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

} // namespace detail
} // namespace gl
} // namespace moge

void moge::gl::createContextD3D11(moge::gl::ContextD3D11& ctx) {
  MOGE_ASSERT(ctx.hwnd);
  MOGE_ASSERT(!ctx.d3d_device && !ctx.d3d_device_context && !ctx.d3d_swap_chain && !ctx.d3d_render_target_view);
  MOGE_ASSERT(!ctx.stride_from_shader);
  MOGE_ASSERT(!ctx.num_byte_of_vbo);

  RECT client_rect;
  BOOL ok = GetClientRect(ctx.hwnd, &client_rect);
  MOGE_ASSERT(ok);

  LONG client_width = client_rect.right - client_rect.left;
  LONG client_height = client_rect.bottom - client_rect.top;

  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

  sd.BufferCount = 2;
  sd.BufferDesc.Width = static_cast<UINT>(client_width);
  sd.BufferDesc.Width = static_cast<UINT>(client_height);
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = ctx.hwnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.Windowed = TRUE;

  const D3D_FEATURE_LEVEL lvl[7] = {
      D3D_FEATURE_LEVEL_11_1,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_9_3,
      D3D_FEATURE_LEVEL_9_2,
      D3D_FEATURE_LEVEL_9_1,
  };

  D3D_FEATURE_LEVEL feature_level_supported;

  UINT device_flags = 0;
#if defined(MOGE_DEBUG)
  device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

  D3D_DRIVER_TYPE driver_type = D3D_DRIVER_TYPE_HARDWARE;
#if defined(MOGE_DEBUG)
  driver_type = D3D_DRIVER_TYPE_WARP;
#endif

  HRESULT hr = D3D11CreateDeviceAndSwapChain(
      NULL,
      driver_type,
      NULL,
      device_flags,
      lvl,
      7, // length of lvl
      D3D11_SDK_VERSION,
      &sd,
      &ctx.d3d_swap_chain,
      &ctx.d3d_device,
      &feature_level_supported,
      &ctx.d3d_device_context);
  MOGE_ASSERT(SUCCEEDED(hr));

  ID3D11Texture2D* backbuffer;
  hr = ctx.d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreateRenderTargetView(backbuffer, NULL, &ctx.d3d_render_target_view);
  MOGE_ASSERT(SUCCEEDED(hr));
  backbuffer->Release();

  ctx.d3d_device_context->OMSetRenderTargets(1, &ctx.d3d_render_target_view, NULL);

  D3D11_VIEWPORT vp;
  ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
  vp.Width = static_cast<float>(client_width);
  vp.Height = static_cast<float>(client_height);
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  ctx.d3d_device_context->RSSetViewports(1, &vp);

  moge::gl::detail::setDefaults(ctx);
}

void moge::gl::destroyContextD3D11(moge::gl::ContextD3D11& ctx) {
  MOGE_ASSERT(ctx.d3d_device);
  MOGE_ASSERT(ctx.d3d_device_context);
  MOGE_ASSERT(ctx.d3d_swap_chain);
  MOGE_ASSERT(ctx.d3d_render_target_view);

  ctx.d3d_device->Release();
  ctx.d3d_device_context->Release();
  ctx.d3d_swap_chain->Release();
  ctx.d3d_render_target_view->Release();

  ctx.d3d_device = NULL;
  ctx.d3d_device_context = NULL;
  ctx.d3d_swap_chain = NULL;
  ctx.d3d_render_target_view = NULL;

  ctx.stride_from_shader = 0;
  ctx.num_byte_of_vbo = 0;
}

void moge::gl::resizeBackBufferD3D11(moge::gl::ContextD3D11& ctx) {
  ctx.d3d_render_target_view->Release();
  ctx.d3d_render_target_view = NULL;

  HRESULT hr;
  hr = ctx.d3d_swap_chain->ResizeBuffers(2, 0, 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
  MOGE_ASSERT(SUCCEEDED(hr));

  ID3D11Texture2D* backbuffer;
  hr = ctx.d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
  MOGE_ASSERT(SUCCEEDED(hr));

  hr = ctx.d3d_device->CreateRenderTargetView(backbuffer, NULL, &ctx.d3d_render_target_view);
  MOGE_ASSERT(SUCCEEDED(hr));
  backbuffer->Release();

  ctx.d3d_device_context->OMSetRenderTargets(1, &ctx.d3d_render_target_view, NULL);

  RECT client_rect;
  BOOL ok = GetClientRect(ctx.hwnd, &client_rect);
  MOGE_ASSERT(ok);

  LONG client_width = client_rect.right - client_rect.left;
  LONG client_height = client_rect.bottom - client_rect.top;

  D3D11_VIEWPORT vp;
  ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
  vp.Width = static_cast<float>(client_width);
  vp.Height = static_cast<float>(client_height);
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;
  ctx.d3d_device_context->RSSetViewports(1, &vp);
}
