module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module Bindable;

namespace fatpound::win32::d3d11
{
    ID3D11DeviceContext* Bindable::GetContext_(Graphics& gfx) noexcept
    {
        return gfx.pContext_.Get();
    }

    ID3D11Device* Bindable::GetDevice_(Graphics& gfx) noexcept
    {
        return gfx.pDevice_.Get();
    }
}