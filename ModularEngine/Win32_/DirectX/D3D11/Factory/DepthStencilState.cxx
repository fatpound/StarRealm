module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilState;

import std;

namespace fatpound::win32::d3d11::factory
{
    void DepthStencilState::Init(
        Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
        Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState,
        const D3D11_DEPTH_STENCIL_DESC& desc
    )
    {
        HRESULT hr = pDevice->CreateDepthStencilState(&desc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }
    }
}