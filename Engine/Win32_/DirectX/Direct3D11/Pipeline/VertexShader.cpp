module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

#if _MSVC_LANG == 202002L
#if IN_DEBUG
#include <string>
#endif // IN_DEBUG
#endif // _MSVC_LANG

module VertexShader;

namespace fatpound::win32::d3d11::pipeline
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