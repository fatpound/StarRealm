module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:SamplerState;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class SamplerState final
    {
    public:
        explicit SamplerState() = delete;
        explicit SamplerState(const SamplerState& src) = delete;
        explicit SamplerState(SamplerState&& src) = delete;

        SamplerState& operator = (const SamplerState& src) = delete;
        SamplerState& operator = (SamplerState&& src) = delete;
        ~SamplerState() noexcept = delete;


    public:
        auto operator <=> (const SamplerState& rhs) const = delete;
        bool operator ==  (const SamplerState& rhs) const = delete;


    public:
        static auto CreateDESC() -> D3D11_SAMPLER_DESC
        {
            D3D11_SAMPLER_DESC desc = {};
            desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
            desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
            desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
            desc.MinLOD = 0.0f;
            desc.MaxLOD = D3D11_FLOAT32_MAX;

            return desc;
        }


    public:
        static void Create(
            const GraphicsResourcePack& gfxResPack,
            ::Microsoft::WRL::ComPtr<ID3D11SamplerState>& pSamplerState,
            D3D11_SAMPLER_DESC desc
        );


    protected:


    private:
    };
}