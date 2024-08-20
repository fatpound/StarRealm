module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:ShaderResource;

import FatPound.Win32.D3D11.Graphics.Resource;
import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class ShaderResource final
	{
	public:
		explicit ShaderResource() = delete;
		explicit ShaderResource(const ShaderResource& src) = delete;
		explicit ShaderResource(ShaderResource&& src) = delete;

		ShaderResource& operator = (const ShaderResource& src) = delete;
		ShaderResource& operator = (ShaderResource&& src) = delete;
		~ShaderResource() noexcept = delete;


	public:
		template <UINT MSAA_Quality, bool ForFramework = true>
		static void SetDefault(GfxResource& gfxres, UINT width, UINT height)
		{
			const auto& t2dDesc = factory::Texture2D::CreateDESC<MSAA_Quality, ForFramework>(width, height);
			factory::Texture2D::Create(gfxres, t2dDesc);

			::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pSysBufferTextureView_ = nullptr;

			const auto& srvDesc = factory::ShaderResourceView::CreateDESC<MSAA_Quality>(t2dDesc.Format);
			factory::ShaderResourceView::Create(gfxres, pSysBufferTextureView_, srvDesc);

			gfxres.m_device_pack.m_pImmediateContext->PSSetShaderResources(0u, 1u, pSysBufferTextureView_.GetAddressOf());
		}


	protected:


	private:
	};
}