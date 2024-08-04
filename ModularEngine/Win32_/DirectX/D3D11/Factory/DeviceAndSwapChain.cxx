module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DeviceAndSwapChain;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DeviceAndSwapChain::Create(
        Microsoft::WRL::ComPtr<ID3D11Device>&        pDevice,
        Microsoft::WRL::ComPtr<IDXGISwapChain>&      pSwapChain,
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext_,
        const DXGI_SWAP_CHAIN_DESC&                  desc
    )
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

        HRESULT hr;

        hr = D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            swapCreateFlags,
            nullptr,
            0u,
            D3D11_SDK_VERSION,
            &desc,
            &pSwapChain,
            &pDevice,
            nullptr,
            &pImmediateContext_
        );

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create the Device and SwapChain!");
        }
    }
}