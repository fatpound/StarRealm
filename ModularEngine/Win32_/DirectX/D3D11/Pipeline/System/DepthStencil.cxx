module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:DepthStencil;

import FatPound.Win32.D3D11.Factory;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
	void DepthStencil::SetDefault(
		::wrl::ComPtr<::ID3D11Device>&        pDevice,
		::wrl::ComPtr<::ID3D11DeviceContext>& pImmediateContext
	)
	{
		::wrl::ComPtr<::ID3D11DepthStencilState> pDSState = nullptr;

		const auto& descDSS = factory::DepthStencilState::CreateDESC();
		factory::DepthStencilState::Create(pDevice, pDSState, descDSS);

		pImmediateContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	}
}