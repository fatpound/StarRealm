module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilView;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilView final
    {
    public:
        explicit DepthStencilView() = delete;
        explicit DepthStencilView(const DepthStencilView& src) = delete;
        explicit DepthStencilView(DepthStencilView&& src) = delete;

        DepthStencilView& operator = (const DepthStencilView& src) = delete;
        DepthStencilView& operator = (DepthStencilView&& src) = delete;
        ~DepthStencilView() noexcept = delete;


    public:
        auto operator <=> (const DepthStencilView& rhs) const = delete;
        bool operator ==  (const DepthStencilView& rhs) const = delete;


    public:
        template <UINT MSAA_Quality>
        static constexpr auto CreateDESC() noexcept -> D3D11_DEPTH_STENCIL_VIEW_DESC
        {
            D3D11_DEPTH_STENCIL_VIEW_DESC desc = {};
            desc.Format = DXGI_FORMAT_D32_FLOAT;

            if constexpr (MSAA_Quality == 1u)
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
                desc.Texture2D.MipSlice = 0u;
            }
            else
            {
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
                desc.Texture2D.MipSlice = 1u;
            }

            return desc;
        }


    public:
        static void Create(
            GraphicsResourcePack& gfxResPack,
            const ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc
        );


    protected:


    private:
    };
}