module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DepthStencilView::Create(
            GraphicsResourcePack& gfxResPack,
            const ::wrl::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc
        )
    {
        const auto hr = gfxResPack.m_pDevice->CreateDepthStencilView(pDepthStencil.Get(), &desc, &gfxResPack.m_pDSV);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }
    }
}