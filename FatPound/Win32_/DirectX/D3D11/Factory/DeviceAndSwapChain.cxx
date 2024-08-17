module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DeviceAndSwapChain;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DeviceAndSwapChain::Create(GfxResource& gfxres, const DXGI_SWAP_CHAIN_DESC& desc)
    {
        static constinit UINT swapCreateFlags;

        if constexpr (IN_RELEASE)
        {
            swapCreateFlags = 0u;
        }
        else
        {
            swapCreateFlags = D3D11_CREATE_DEVICE_DEBUG;
        }

        const auto hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            swapCreateFlags,
            nullptr,
            0u,
            D3D11_SDK_VERSION,
            &desc,
            &gfxres.m_pSwapChain,
            &gfxres.m_pDevice,
            nullptr,
            &gfxres.m_pImmediateContext
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create the Device and SwapChain!");
        }
    }
}