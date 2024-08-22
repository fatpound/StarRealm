module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Element:VertexShader;

namespace fatpound::win32::d3d11::pipeline::element
{
    VertexShader::VertexShader(ID3D11Device* pDevice, const std::wstring& path)
    {
        ::D3DReadFileToBlob(path.c_str(), &m_pBytecodeBlob_);

        pDevice->CreateVertexShader(
            m_pBytecodeBlob_->GetBufferPointer(),
            m_pBytecodeBlob_->GetBufferSize(),
            nullptr,
            &m_pVertexShader_
        );
    }

    auto VertexShader::GetBytecode() const noexcept -> ID3DBlob*
    {
        return m_pBytecodeBlob_.Get();
    }

    void VertexShader::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->VSSetShader(m_pVertexShader_.Get(), nullptr, 0u);
    }
}