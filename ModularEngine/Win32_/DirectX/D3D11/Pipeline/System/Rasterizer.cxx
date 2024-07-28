module;

#include "../../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Rasterizer;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
    void Rasterizer::SetDefault(
        wrl::ComPtr<ID3D11Device>& pDevice,
        wrl::ComPtr<ID3D11DeviceContext>& pContext)
    {
        HRESULT hr;

        wrl::ComPtr<ID3D11RasterizerState> pRasterState;

        D3D11_RASTERIZER_DESC rasterDesc = {};
        rasterDesc.FillMode = D3D11_FILL_SOLID;
        rasterDesc.CullMode = D3D11_CULL_BACK;
        rasterDesc.FrontCounterClockwise = false;
        rasterDesc.DepthBias = 0;
        rasterDesc.DepthBiasClamp = 0.0f;
        rasterDesc.SlopeScaledDepthBias = 0.0f;
        rasterDesc.DepthClipEnable = true;
        rasterDesc.ScissorEnable = false;
        rasterDesc.MultisampleEnable = true;
        rasterDesc.AntialiasedLineEnable = true;

        hr = pDevice->CreateRasterizerState(&rasterDesc, &pRasterState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RasterizerState!");
        }

        pContext->RSSetState(pRasterState.Get());
    }
}