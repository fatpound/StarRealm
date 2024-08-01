module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Rasterizer final
	{
	public:
		static void SetDefault(
			Microsoft::WRL::ComPtr<ID3D11Device>&          pDevice,
			Microsoft::WRL::ComPtr<ID3D11DeviceContext>&   pContext
		);


	protected:


	private:
	};
}