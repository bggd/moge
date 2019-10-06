#ifndef MOGE_SRC_D3D11_HPP_INCLUDED
#define MOGE_SRC_D3D11_HPP_INCLUDED

#include <assert.h>
#include <d3d11.h>
#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "winmm.lib")

namespace moge {

struct D3D11 {

  HWND hwnd = nullptr;
  ID3D11Device* d3d_device = nullptr;
  ID3D11DeviceContext* d3d_device_context = nullptr;
  IDXGISwapChain* d3d_swap_chain = nullptr;
  ID3D11RenderTargetView* d3d_render_target_view = nullptr;

  void init_d3d11(HWND handle) {
    assert(this->hwnd == nullptr);
    assert(this->d3d_device == nullptr && this->d3d_device_context == nullptr && this->d3d_swap_chain == nullptr && this->d3d_render_target_view == nullptr);
    this->hwnd = handle;

    RECT client_rect;
    GetClientRect(this->hwnd, &client_rect);

    auto client_width = client_rect.right - client_rect.left;
    auto client_height = client_rect.bottom - client_rect.top;

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));

    sd.BufferCount = 1;
    sd.BufferDesc.Width = client_width;
    sd.BufferDesc.Height = client_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = this->hwnd;
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
        D3D_FEATURE_LEVEL_9_1};

    D3D_FEATURE_LEVEL feature_levels_supported;

    UINT device_flags = 0;
#ifdef _DEBUG
    device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        device_flags,
        lvl,
        7,
        D3D11_SDK_VERSION,
        &sd,
        &this->d3d_swap_chain,
        &this->d3d_device,
        &feature_levels_supported,
        &this->d3d_device_context);
    assert(SUCCEEDED(hr));

    ID3D11Texture2D* backbuffer;
    hr = this->d3d_swap_chain->GetBuffer(0, IID_PPV_ARGS(&backbuffer));
    assert(SUCCEEDED(hr));

    hr = this->d3d_device->CreateRenderTargetView(backbuffer, nullptr, &this->d3d_render_target_view);
    assert(SUCCEEDED(hr));
    backbuffer->Release();

    this->d3d_device_context->OMSetRenderTargets(1, &this->d3d_render_target_view, nullptr);

    D3D11_VIEWPORT vp;
    ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
    vp.Width = client_width;
    vp.Height = client_height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    this->d3d_device_context->RSSetViewports(1, &vp);
  }

  void deinit_d3d11() {
    assert(this->d3d_device && this->d3d_device_context && this->d3d_swap_chain && this->d3d_render_target_view);
    this->d3d_swap_chain->Release();
    this->d3d_render_target_view->Release();
    this->d3d_device->Release();
    this->d3d_device_context->Release();
  }

  void clear(float R, float G, float B, float A) {
    float col[4] = {R, G, B, A};
    this->d3d_device_context->ClearRenderTargetView(this->d3d_render_target_view, col);
  }

  void present() { this->d3d_swap_chain->Present(0, 0); }
}; // struct D3D11
} // namespace moge

#endif // MOGE_SRC_D3D11_HPP_INCLUDED
