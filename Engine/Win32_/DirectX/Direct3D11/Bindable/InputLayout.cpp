module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

module InputLayout;

namespace fatpound::win32::d3d11
{
    InputLayout::InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
    {
        GetDevice_(gfx)->CreateInputLayout(
            layout.data(),
            static_cast<UINT>(layout.size()),
            pVertexShaderBytecode->GetBufferPointer(),
            pVertexShaderBytecode->GetBufferSize(),
            &pInputLayout_
        );
    }

    void InputLayout::Bind(Graphics& gfx) noexcept
    {
        GetContext_(gfx)->IASetInputLayout(pInputLayout_.Get());
    }
}