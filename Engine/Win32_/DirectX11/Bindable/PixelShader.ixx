module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module PixelShader;

import D3D11Graphics;
import Bindable;

#ifdef NDEBUG
import std.core;
#else
import <string>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class PixelShader : public Bindable
    {
    public:
        PixelShader(fatpound::dx11::D3DGraphics& gfx, const std::wstring& path);


    public:
        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader_;


    private:
    };
}