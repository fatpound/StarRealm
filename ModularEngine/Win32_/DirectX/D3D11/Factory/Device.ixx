module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:Device;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class Device final
    {
    public:
        static void CreateWithSwapChain(
            Microsoft::WRL::ComPtr<ID3D11Device>&        pDevice,
            Microsoft::WRL::ComPtr<IDXGISwapChain>&      pSwapChain,
            Microsoft::WRL::ComPtr<ID3D11DeviceContext>& pImmediateContext_,
            const DXGI_SWAP_CHAIN_DESC&                  desc
        );


    protected:


    private:
    };
}