module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:RenderTarget;

import FatPound.Win32.D3D11.Graphics.Resource;
import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class RenderTarget final
	{
	public:
		explicit RenderTarget() = delete;
		explicit RenderTarget(const RenderTarget& src) = delete;
		explicit RenderTarget(RenderTarget&& src) = delete;

		RenderTarget& operator = (const RenderTarget& src) = delete;
		RenderTarget& operator = (RenderTarget&& src) = delete;
		~RenderTarget() noexcept = delete;


	public:
		template <UINT MSAA_Quality, bool ForFramework = false>
		static void SetDefault(GfxResource& gfxres, UINT width, UINT height)
		{
			factory::RenderTargetView::Create(gfxres);

			::Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D = nullptr;

			const auto& descTex2D = factory::Texture2D::CreateDESC<MSAA_Quality>(width, height);
			factory::Texture2D::Create(gfxres, pTexture2D, descTex2D);

			if constexpr (not ForFramework)
			{
				const auto& descDSV = factory::DepthStencilView::CreateDESC<MSAA_Quality>();
				factory::DepthStencilView::Create(gfxres, pTexture2D, descDSV);
			}

			gfxres.m_device_pack.m_pImmediateContext->OMSetRenderTargets(1u, gfxres.m_pTarget.GetAddressOf(), gfxres.m_pDSV.Get());
		}


	protected:


	private:
	};
}