module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:Texture2D;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Texture2D::Create(
        const GraphicsResourcePack& gfxResPack,
        ::wrl::ComPtr<ID3D11Texture2D>& pTexture2D,
        const D3D11_TEXTURE2D_DESC& desc
    )
    {
        const auto hr = gfxResPack.m_pDevice->CreateTexture2D(&desc, nullptr, &pTexture2D);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }
    }

    void Texture2D::Create(
        GraphicsResourcePack& gfxResPack,
        const D3D11_TEXTURE2D_DESC& desc
    )
    {
        Create(gfxResPack, gfxResPack.m_pSysBufferTexture, desc);
    }
}