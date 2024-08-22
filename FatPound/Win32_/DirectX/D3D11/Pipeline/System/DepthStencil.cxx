module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:DepthStencil;

import FatPound.Win32.D3D11.Factory;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
	void DepthStencil::SetDefault(const GraphicsResourcePack& gfxResPack)
	{
		::wrl::ComPtr<ID3D11DepthStencilState> pDSState = nullptr;

		const auto& descDSS = factory::DepthStencilState::CreateDESC();
		factory::DepthStencilState::Create(gfxResPack, pDSState, descDSS);

		gfxResPack.m_pImmediateContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	}
}