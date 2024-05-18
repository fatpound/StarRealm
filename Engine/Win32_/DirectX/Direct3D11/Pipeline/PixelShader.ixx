module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

#if _MSVC_LANG == 202002L
#if IN_DEBUG
#include <string>
#endif // IN_DEBUG
#endif // _MSVC_LANG

export module PixelShader;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11::pipeline
{
    class PixelShader final : public Bindable
    {
    public:
        PixelShader(NAMESPACE_D3D11::Graphics& gfx, const std::wstring& path);


    public:
        virtual void Bind(NAMESPACE_D3D11::Graphics& gfx) noexcept override final;


    protected:
        Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader_;


    private:
    };
}