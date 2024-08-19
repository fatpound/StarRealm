module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RasterizerState;

import FatPound.Win32.D3D11.Graphics.Resource;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class RasterizerState final
    {
    public:
        explicit RasterizerState() = delete;
        explicit RasterizerState(const RasterizerState& src) = delete;
        explicit RasterizerState(RasterizerState&& src) = delete;

        RasterizerState& operator = (const RasterizerState& src) = delete;
        RasterizerState& operator = (RasterizerState&& src) = delete;
        ~RasterizerState() noexcept = delete;


    public:
        static constexpr auto CreateDESC() noexcept -> D3D11_RASTERIZER_DESC
        {
            D3D11_RASTERIZER_DESC desc = {};
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

        static void Create(
            const GfxResource& gfxres,
            ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState,
            const D3D11_RASTERIZER_DESC& desc
        );


    protected:


    private:
    };
}