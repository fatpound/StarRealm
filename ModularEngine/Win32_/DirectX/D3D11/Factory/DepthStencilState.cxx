module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilState;

import std;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    auto DepthStencilState::CreateDESC() -> D3D11_DEPTH_STENCIL_DESC
    {
        D3D11_DEPTH_STENCIL_DESC desc = {};
        desc.DepthEnable = true;
        desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        desc.DepthFunc = D3D11_COMPARISON_LESS;

        return desc;
    }

    void DepthStencilState::Create(
        wrl::ComPtr<ID3D11Device>&            pDevice,
        wrl::ComPtr<ID3D11DepthStencilState>& pDSState,
        const D3D11_DEPTH_STENCIL_DESC&       desc
    )
    {
        HRESULT hr;

        hr = pDevice->CreateDepthStencilState(&desc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }
    }
}