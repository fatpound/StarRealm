module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:ShaderResourceView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void ShaderResourceView::Create(
        const GraphicsResourcePack& gfxResPack,
        ::wrl::ComPtr<ID3D11ShaderResourceView>& pSysBufferTextureView,
        D3D11_SHADER_RESOURCE_VIEW_DESC desc
    )
    {
        HRESULT hr;

        hr = gfxResPack.m_pDevice->CreateShaderResourceView(gfxResPack.m_pSysBufferTexture.Get(), &desc, &pSysBufferTextureView);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create ShaderResourceView!");
        }
    }
}