module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

import FatPound.Win32.D3D11.Graphics.Resource;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Rasterizer final
	{
	public:
		explicit Rasterizer() = delete;
		explicit Rasterizer(const Rasterizer& src) = delete;
		explicit Rasterizer(Rasterizer&& src) = delete;

		Rasterizer& operator = (const Rasterizer& src) = delete;
		Rasterizer& operator = (Rasterizer&& src) = delete;
		~Rasterizer() noexcept = delete;


	public:
		static void SetDefault(GfxResource& gfxres);


	protected:


	private:
	};
}