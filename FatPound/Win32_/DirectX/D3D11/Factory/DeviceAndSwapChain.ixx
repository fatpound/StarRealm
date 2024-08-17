module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DeviceAndSwapChain;

import FatPound.Win32.D3D11.Graphics.Resource;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DeviceAndSwapChain final
    {
    public:
        explicit DeviceAndSwapChain() = delete;
        explicit DeviceAndSwapChain(const DeviceAndSwapChain& src) = delete;
        explicit DeviceAndSwapChain(DeviceAndSwapChain&& src) = delete;

        DeviceAndSwapChain& operator = (const DeviceAndSwapChain& src) = delete;
        DeviceAndSwapChain& operator = (DeviceAndSwapChain&& src) = delete;
        ~DeviceAndSwapChain() noexcept = delete;


    public:
        template <UINT MSAA_Quality>
        static auto CreateDESC(HWND hWnd, UINT width, UINT height) -> DXGI_SWAP_CHAIN_DESC
        {
            DXGI_SWAP_CHAIN_DESC desc = {};
            desc.BufferDesc.Width = width;
            desc.BufferDesc.Height = height;
            desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
            desc.BufferDesc.RefreshRate.Numerator = 0u;
            desc.BufferDesc.RefreshRate.Denominator = 0u;
            desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
            desc.SampleDesc.Count = MSAA_Quality;
            desc.SampleDesc.Quality = 0u;
            desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            desc.BufferCount = 1u;
            desc.OutputWindow = hWnd;
            desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
            desc.Flags = 0u;

            if constexpr (IN_RELEASE)
            {
                desc.Windowed = false;
            }
            else
            {
                desc.Windowed = true;
            }

            return desc;
        }


    public:
        static void Create(GfxResource& gfxres, const DXGI_SWAP_CHAIN_DESC& desc);


    protected:


    private:
    };
}