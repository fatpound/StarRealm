module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module InputLayout;

import D3D11Graphics;
import Bindable;

#ifdef NDEBUG
import std.core;
#else
import <vector>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class InputLayout : public Bindable
    {
    public:
        InputLayout(fatpound::dx11::D3DGraphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode);


    public:
        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout_;


    private:
    };
}