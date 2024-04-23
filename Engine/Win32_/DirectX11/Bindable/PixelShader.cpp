module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

module PixelShader;

namespace fatpound::starrealm
{
    PixelShader::PixelShader(fatpound::dx11::D3DGraphics& gfx, const std::wstring& path)
    {
        Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

        D3DReadFileToBlob(path.c_str(), &pBlob);

        GetDevice_(gfx)->CreatePixelShader(
            pBlob->GetBufferPointer(),
            pBlob->GetBufferSize(),
            nullptr,
            &pPixelShader_
        );
    }

    void PixelShader::Bind(fatpound::dx11::D3DGraphics& gfx) noexcept
    {
        GetContext_(gfx)->PSSetShader(pPixelShader_.Get(), nullptr, 0u);
    }
}