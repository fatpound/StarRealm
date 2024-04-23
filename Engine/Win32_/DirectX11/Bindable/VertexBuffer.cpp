module;

#include "../../FatWin32_.hpp"

#include <wrl.h>

module VertexBuffer;

namespace fatpound::starrealm
{
    void VertexBuffer::Bind(fatpound::dx11::D3DGraphics& gfx) noexcept
    {
        const UINT offset = 0u;

        GetContext_(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer_.GetAddressOf(), &stride_, &offset);
    }
}