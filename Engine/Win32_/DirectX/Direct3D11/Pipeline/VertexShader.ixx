module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

#if _MSVC_LANG == 202002L
#if IN_DEBUG
#include <string>
#endif // IN_DEBUG
#endif // _MSVC_LANG

export module VertexShader;

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
    class VertexShader final : public Bindable
    {
    public:
        VertexShader(NAMESPACE_D3D11::Graphics& gfx, const std::wstring& path);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    public:
        ID3DBlob* GetBytecode() const noexcept;


    protected:
        Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob_;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader_;


    private:
    };
}