module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Viewport;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::pipeline::system
{
	class Viewport final
	{
	public:
		explicit Viewport() = delete;
		explicit Viewport(const Viewport& src) = delete;
		explicit Viewport(Viewport&& src) = delete;

		Viewport& operator = (const Viewport& src) = delete;
		Viewport& operator = (Viewport&& src) = delete;
		~Viewport() noexcept = delete;


	public:
		auto operator <=> (const Viewport& rhs) const = delete;
		bool operator ==  (const Viewport& rhs) const = delete;


	public:
		static void SetDefault(const GfxResourcePack& gfxResPack, std::size_t width, std::size_t height);


	protected:


	private:
	};
}