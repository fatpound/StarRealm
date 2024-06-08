module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

module Direct3D11.Pipeline.Bindable;

namespace fatpound::win32::d3d11::pipeline
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