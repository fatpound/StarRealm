module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Element:PixelShader;

namespace fatpound::win32::d3d11::pipeline::element
{
    PixelShader::PixelShader(ID3D11Device* pDevice, const std::wstring& path)
    {
        ::Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

        ::D3DReadFileToBlob(path.c_str(), &pBlob);

        pDevice->CreatePixelShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &m_pPixelShader_
        );
    }

    void PixelShader::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0u);
    }
}