#include "context.hpp"

#include <limits.h>
#include <stdlib.h>

#include "../../macro.hpp"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "winmm.lib")

void moge::gl::createContextD3D11(moge::gl::ContextD3D11& ctx) {
  MOGE_ASSERT(ctx.hwnd);
  MOGE_ASSERT(!ctx.d3d_device && !ctx.d3d_device_context && !ctx.d3d_swap_chain && !ctx.d3d_render_target_view);
  MOGE_ASSERT(!ctx.stride_from_shader);

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
}
