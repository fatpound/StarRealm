module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Sampler;

import FatPound.Win32.D3D11.Graphics.Resource;
import FatPound.Win32.D3D11.Factory;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Sampler final
	{
	public:
		explicit Sampler() = delete;
		explicit Sampler(const Sampler& src) = delete;
		explicit Sampler(Sampler&& src) = delete;

		Sampler& operator = (const Sampler& src) = delete;
		Sampler& operator = (Sampler&& src) = delete;
		~Sampler() noexcept = delete;


	public:
		static void SetDefault(GfxResource& gfxres);


	protected:


	private:
	};
}