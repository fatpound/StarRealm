module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RenderTargetView;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class RenderTargetView final
    {
    public:
        explicit RenderTargetView() = delete;
        explicit RenderTargetView(const RenderTargetView& src) = delete;
        explicit RenderTargetView(RenderTargetView&& src) = delete;

        RenderTargetView& operator = (const RenderTargetView& src) = delete;
        RenderTargetView& operator = (RenderTargetView&& src) = delete;
        ~RenderTargetView() noexcept = delete;


    public:
        static void Create(
            ::Microsoft::WRL::ComPtr<ID3D11Device>&           pDevice,
            ::Microsoft::WRL::ComPtr<IDXGISwapChain>&         pSwapChain,
            ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pTarget
        );


    protected:


    private:
    };
}