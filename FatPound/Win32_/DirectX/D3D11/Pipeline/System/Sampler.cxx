module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Sampler;

namespace fatpound::win32::d3d11::pipeline::system
{
	void Sampler::SetDefault(GfxResource& gfxres)
	{
        ::Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState_ = nullptr;

        const auto& sampDesc = factory::SamplerState::CreateDESC();

        factory::SamplerState::Create(gfxres, pSamplerState_, sampDesc);

        gfxres.m_pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState_.GetAddressOf());
	}
}