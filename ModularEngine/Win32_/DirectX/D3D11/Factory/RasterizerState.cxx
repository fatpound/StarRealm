module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:RasterizerState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    auto RasterizerState::CreateDESC() -> ::D3D11_RASTERIZER_DESC
    {
        ::D3D11_RASTERIZER_DESC desc = {};
        desc.FillMode = D3D11_FILL_SOLID;
        desc.CullMode = D3D11_CULL_BACK;
        desc.FrontCounterClockwise = false;
        desc.DepthBias = 0;
        desc.DepthBiasClamp = 0.0f;
        desc.SlopeScaledDepthBias = 0.0f;
        desc.DepthClipEnable = true;
        desc.ScissorEnable = false;
        desc.MultisampleEnable = true;
        desc.AntialiasedLineEnable = true;

        return desc;
    }

    void RasterizerState::Create(
        ::wrl::ComPtr<::ID3D11Device>&          pDevice,
        ::wrl::ComPtr<::ID3D11RasterizerState>& pRasterizerState,
        const ::D3D11_RASTERIZER_DESC&          desc
    )
    {
        ::HRESULT hr;

        hr = pDevice->CreateRasterizerState(&desc, &pRasterizerState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RasterizerState!");
        }
    }
}