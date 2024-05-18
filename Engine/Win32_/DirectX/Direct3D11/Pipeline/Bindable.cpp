module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module Bindable;

namespace fatpound::win32::d3d11::pipeline
{
    ID3D11DeviceContext* Bindable::GetContext_(D3D11_NAMESPACE::Graphics& gfx) noexcept
    {
        return gfx.pContext_.Get();
    }

    ID3D11Device* Bindable::GetDevice_(D3D11_NAMESPACE::Graphics& gfx) noexcept
    {
        return gfx.pDevice_.Get();
    }
}