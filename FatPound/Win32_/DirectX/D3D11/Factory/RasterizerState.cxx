module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:RasterizerState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void RasterizerState::Create(
        const GraphicsResourcePack& gfxResPack,
        ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState,
        const D3D11_RASTERIZER_DESC& desc
    )
    {
        const auto hr = gfxResPack.m_pDevice->CreateRasterizerState(&desc, &pRasterizerState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RasterizerState!");
        }
    }
}