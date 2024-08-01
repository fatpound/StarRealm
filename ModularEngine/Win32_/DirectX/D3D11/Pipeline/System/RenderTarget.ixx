module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:RenderTarget;

import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class RenderTarget final
	{
	public:
		template <UINT MSAA_Quality>
		static void SetDefault(
			Microsoft::WRL::ComPtr<ID3D11Device>&           pDevice,
			Microsoft::WRL::ComPtr<IDXGISwapChain>&         pSwapChain,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext>&    pImmediateContext,
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pRenderTargetView,
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& pDSV,
			UINT width,
			UINT height
		)
		{
			factory::RenderTargetView::Create(pDevice, pSwapChain, pRenderTargetView);

			Microsoft::WRL::ComPtr<ID3D11Texture2D> pTexture2D = nullptr;

			const auto& descTex2D = factory::Texture2D::CreateDESC<MSAA_Quality>(width, height);
			factory::Texture2D::Create(pDevice, pTexture2D, descTex2D);

			const auto& descDSV = factory::DepthStencilView::CreateDESC<MSAA_Quality>();
			factory::DepthStencilView::Create(pDevice, pTexture2D, pDSV, descDSV);

			pImmediateContext->OMSetRenderTargets(1u, pRenderTargetView.GetAddressOf(), pDSV.Get());
		}


	protected:


	private:
	};
}