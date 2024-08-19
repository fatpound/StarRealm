module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:RenderTargetView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void RenderTargetView::Create(GfxResource& gfxres)
    {
        ::wrl::ComPtr<ID3D11Texture2D> pBackBufferTexture = nullptr;

        HRESULT hr;

        hr = gfxres.m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }

        hr = gfxres.m_pDevice->CreateRenderTargetView(pBackBufferTexture.Get(), nullptr, &gfxres.m_pTarget);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }
    }
}