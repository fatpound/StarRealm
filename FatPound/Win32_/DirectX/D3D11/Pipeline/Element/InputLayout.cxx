module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Element:InputLayout;

namespace fatpound::win32::d3d11::pipeline::element
{
    InputLayout::InputLayout(ID3D11Device* pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode)
    {
        pDevice->CreateInputLayout(
            layout.data(),
            static_cast<UINT>(layout.size()),
            pVertexShaderBytecode->GetBufferPointer(),
            pVertexShaderBytecode->GetBufferSize(),
            &m_pInputLayout_
        );
    }

    void InputLayout::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->IASetInputLayout(m_pInputLayout_.Get());
    }
}