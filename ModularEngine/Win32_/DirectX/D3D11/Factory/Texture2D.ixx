module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory:Texture2D;

import std;

export namespace fatpound::win32::d3d11::factory
{
    class Texture2D final
    {
    public:
        template <UINT MSAA_Quality>
        static auto CreateDESC(UINT width, UINT height) -> D3D11_TEXTURE2D_DESC
        {
            D3D11_TEXTURE2D_DESC desc = {};
            desc.Width = width;
            desc.Height = height;
            desc.MipLevels = 1u;
            desc.ArraySize = 1u;
            desc.Format = DXGI_FORMAT_D32_FLOAT;
            desc.SampleDesc.Count = MSAA_Quality;
            desc.SampleDesc.Quality = 0u;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

            return desc;
        }


    public:
        static void Create(
            Microsoft::WRL::ComPtr<ID3D11Device>&    pDevice,
            Microsoft::WRL::ComPtr<ID3D11Texture2D>& pTexture2D,
            const D3D11_TEXTURE2D_DESC&              desc
        );


    protected:


    private:
    };
}