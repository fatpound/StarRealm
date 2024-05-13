module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module InputLayout;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
#else
import <vector>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    class InputLayout final : public Bindable
    {
    public:
        InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout_;


    private:
    };
}