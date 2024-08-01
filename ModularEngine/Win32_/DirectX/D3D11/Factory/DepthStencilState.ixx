module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilState;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilState final
    {
    public:
        static auto CreateDESC() -> D3D11_DEPTH_STENCIL_DESC;


    public:
        static void Create(
            Microsoft::WRL::ComPtr<ID3D11Device>&            pDevice,
            Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState,
            const D3D11_DEPTH_STENCIL_DESC&                  desc
        );


    protected:


    private:
    };
}