module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RenderTargetView;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class RenderTargetView final
    {
    public:
        static void Init(
            Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
            Microsoft::WRL::ComPtr<IDXGISwapChain>& pSwapChain,
            Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pTarget
        );


    protected:


    private:
    };
}