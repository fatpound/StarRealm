module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DepthStencilState::Create(
        const GraphicsResourcePack& gfxResPack,
        ::wrl::ComPtr<ID3D11DepthStencilState>& pDSState,
        const D3D11_DEPTH_STENCIL_DESC& desc
        )
    {
        const auto hr = gfxResPack.m_pDevice->CreateDepthStencilState(&desc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }
    }
}