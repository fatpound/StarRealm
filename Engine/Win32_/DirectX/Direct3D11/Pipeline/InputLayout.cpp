module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module InputLayout;

namespace fatpound::win32::d3d11::pipeline
{
    InputLayout::InputLayout(D3D11_NAMESPACE::Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
    {
        Bindable::GetDevice_(gfx)->CreateInputLayout(
            layout.data(),
            static_cast<UINT>(layout.size()),
            pVertexShaderBytecode->GetBufferPointer(),
            pVertexShaderBytecode->GetBufferSize(),
            &pInputLayout_
        );
    }

    void InputLayout::Bind(D3D11_NAMESPACE::Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->IASetInputLayout(pInputLayout_.Get());
    }
}