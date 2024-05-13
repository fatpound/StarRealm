module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

export module PixelShader;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
#else
import <string>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    class PixelShader final : public Bindable
    {
    public:
        PixelShader(Graphics& gfx, const std::wstring& path);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader_;


    private:
    };
}