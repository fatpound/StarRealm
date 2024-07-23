module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline:PixelShader;

namespace fatpound::win32::d3d11::pipeline
{
    PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
    {
        Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

        D3DReadFileToBlob(path.c_str(), &pBlob);

        Bindable::GetDevice_(gfx)->CreatePixelShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &pPixelShader_
        );
    }

    void PixelShader::Bind(Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->PSSetShader(pPixelShader_.Get(), nullptr, 0u);
    }
}