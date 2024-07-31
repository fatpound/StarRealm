module;

#include "../../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:DepthStencil;

import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class DepthStencil final
	{
	public:
		static void SetDefault(
			Microsoft::WRL::ComPtr<ID3D11Device>&        pDevice,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext
		);


	protected:


	private:
	};
}