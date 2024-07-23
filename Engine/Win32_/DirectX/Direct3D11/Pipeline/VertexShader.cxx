module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline:VertexShader;

namespace fatpound::win32::d3d11::pipeline
{
    VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
    {
        ::D3DReadFileToBlob(path.c_str(), &pBytecodeBlob_);

        Bindable::GetDevice_(gfx)->CreateVertexShader(
            pBytecodeBlob_->GetBufferPointer(),
            pBytecodeBlob_->GetBufferSize(),
            nullptr,
            &pVertexShader_
        );
    }

    auto VertexShader::GetBytecode() const noexcept -> ID3DBlob*
    {
        return pBytecodeBlob_.Get();
    }

    void VertexShader::Bind(Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->VSSetShader(pVertexShader_.Get(), nullptr, 0u);
    }
}