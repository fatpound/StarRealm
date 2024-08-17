module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:DepthStencilState;

import FatPound.Win32.D3D11.Graphics.Resource;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class DepthStencilState final
    {
    public:
        explicit DepthStencilState() = delete;
        explicit DepthStencilState(const DepthStencilState& src) = delete;
        explicit DepthStencilState(DepthStencilState&& src) = delete;

        DepthStencilState& operator = (const DepthStencilState& src) = delete;
        DepthStencilState& operator = (DepthStencilState&& src) = delete;
        ~DepthStencilState() noexcept = delete;


    public:
        static auto CreateDESC() -> D3D11_DEPTH_STENCIL_DESC;

        static void Create(
            const GfxResource& gfxres,
            Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState,
            const D3D11_DEPTH_STENCIL_DESC& desc
        );


    protected:


    private:
    };
}