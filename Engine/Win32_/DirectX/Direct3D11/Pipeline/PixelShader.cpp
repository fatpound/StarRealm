module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

#if _MSVC_LANG == 202002L
#if IN_DEBUG
#include <string>
#endif // IN_DEBUG
#endif // _MSVC_LANG

module PixelShader;

import <d3dcompiler.h>;

namespace fatpound::win32::d3d11::pipeline
{
    PixelShader::PixelShader(NAMESPACE_D3D11::Graphics& gfx, const std::wstring& path)
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

    void PixelShader::Bind(NAMESPACE_D3D11::Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->PSSetShader(pPixelShader_.Get(), nullptr, 0u);
    }
}