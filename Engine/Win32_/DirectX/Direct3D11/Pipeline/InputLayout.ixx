module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module InputLayout;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11::pipeline
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