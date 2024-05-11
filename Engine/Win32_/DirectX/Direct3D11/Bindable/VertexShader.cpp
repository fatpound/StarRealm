module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module VertexShader;

import <d3dcompiler.h>;

namespace fatpound::win32::d3d11
{
    VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
    {
        D3DReadFileToBlob(path.c_str(), &pBytecodeBlob_);

        Bindable::GetDevice_(gfx)->CreateVertexShader(
            pBytecodeBlob_->GetBufferPointer(),
            pBytecodeBlob_->GetBufferSize(),
            nullptr,
            &pVertexShader_
        );
    }

    ID3DBlob* VertexShader::GetBytecode() const noexcept
    {
        return pBytecodeBlob_.Get();
    }

    void VertexShader::Bind(Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->VSSetShader(pVertexShader_.Get(), nullptr, 0u);
    }
}