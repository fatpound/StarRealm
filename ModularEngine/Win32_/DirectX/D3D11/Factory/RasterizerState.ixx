module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:RasterizerState;

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
        static auto CreateDESC() -> D3D11_RASTERIZER_DESC;

        static void Create(
            ::Microsoft::WRL::ComPtr<ID3D11Device>&          pDevice,
            ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState,
            const D3D11_RASTERIZER_DESC&                     desc
        );


    protected:


    private:
    };
}