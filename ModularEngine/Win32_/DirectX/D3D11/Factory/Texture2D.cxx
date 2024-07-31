module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:Texture2D;

import std;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Texture2D::Create(
        wrl::ComPtr<ID3D11Device>&    pDevice,
        wrl::ComPtr<ID3D11Texture2D>& pTexture2D,
        const D3D11_TEXTURE2D_DESC&   desc
    )
    {
        HRESULT hr;

        hr = pDevice->CreateTexture2D(&desc, nullptr, &pTexture2D);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create Texture2D!");
        }
    }
}