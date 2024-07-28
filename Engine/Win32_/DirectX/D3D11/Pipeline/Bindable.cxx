module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Bindable;

namespace fatpound::win32::d3d11::pipeline
{
    auto Bindable::GetDevice_(Graphics& gfx) noexcept -> ID3D11Device*
    {
        return gfx.pDevice_.Get();
    }

    auto Bindable::GetContext_(Graphics& gfx) noexcept -> ID3D11DeviceContext*
    {
        return gfx.pContext_.Get();
    }
}