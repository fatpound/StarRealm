module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RasterizerState;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

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
        auto operator <=> (const RasterizerState& rhs) const = delete;
        bool operator ==  (const RasterizerState& rhs) const = delete;


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
            const GraphicsResourcePack& gfxResPack,
            ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState,
            const D3D11_RASTERIZER_DESC& desc
        );


    protected:


    private:
    };
}