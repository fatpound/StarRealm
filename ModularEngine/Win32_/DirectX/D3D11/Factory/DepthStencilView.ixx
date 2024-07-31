module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilView;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilView final
    {
    public:
        template <UINT MSAA_Quality>
        static auto CreateDESC() -> D3D11_DEPTH_STENCIL_VIEW_DESC
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_D32_FLOAT;
            desc.Texture2D.MipSlice = 0u;

            if constexpr (MSAA_Quality == 1u)
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            }
            else
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
            }

            return desc;
        }


    public:
        static void Init(
            Microsoft::WRL::ComPtr<ID3D11Device>&           pDevice,
            Microsoft::WRL::ComPtr<ID3D11Texture2D>&        DepthStencil,
            Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& pDSV,
            const D3D11_DEPTH_STENCIL_VIEW_DESC&            desc
        );


    protected:


    private:
    };
}