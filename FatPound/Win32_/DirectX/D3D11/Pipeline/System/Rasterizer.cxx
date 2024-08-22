module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

import FatPound.Win32.D3D11.Factory;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
    void Rasterizer::SetDefault(GraphicsResourcePack& gfxResPack)
    {
        ::wrl::ComPtr<ID3D11RasterizerState> pRasterizerState = nullptr;

        const auto& descRS = factory::RasterizerState::CreateDESC();
        factory::RasterizerState::Create(gfxResPack, pRasterizerState, descRS);

        gfxResPack.m_pImmediateContext->RSSetState(pRasterizerState.Get());
    }
}