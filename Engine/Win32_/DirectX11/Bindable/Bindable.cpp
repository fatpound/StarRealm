module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

module Bindable;

namespace fatpound::starrealm
{
    ID3D11DeviceContext* Bindable::GetContext_(fatpound::dx11::D3DGraphics& gfx) noexcept
    {
        return gfx.pContext_.Get();
    }

    ID3D11Device* Bindable::GetDevice_(fatpound::dx11::D3DGraphics& gfx) noexcept
    {
        return gfx.pDevice_.Get();
    }
}