module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.System:Viewport;

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
		static void SetDefault(
			::Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pContext,
			std::size_t width,
			std::size_t height
		);


	protected:


	private:
	};
}