module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DepthStencilView::Create(
        ::wrl::ComPtr<::ID3D11Device>&           pDevice,
        ::wrl::ComPtr<::ID3D11Texture2D>&        pDepthStencil,
        ::wrl::ComPtr<::ID3D11DepthStencilView>& pDSV,
        const ::D3D11_DEPTH_STENCIL_VIEW_DESC&   desc
    )
    {
        const auto hr = pDevice->CreateDepthStencilView(pDepthStencil.Get(), &desc, &pDSV);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }
    }
}