module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:Texture2D;

import std;

namespace fatpound::win32::d3d11::factory
{
    void Texture2D::Init(
        Microsoft::WRL::ComPtr<ID3D11Device>& pDevice,
        Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
        const D3D11_TEXTURE2D_DESC& desc
    )
    {
        HRESULT hr = pDevice->CreateTexture2D(&desc, nullptr, &pDepthStencil);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }
    }
}