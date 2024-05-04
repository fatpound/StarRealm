module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module VertexBuffer;

namespace fatpound::win32::d3d11
{
    void VertexBuffer::Bind(Graphics& gfx) noexcept
    {
        const UINT offset = 0u;

        GetContext_(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer_.GetAddressOf(), &stride_, &offset);
    }
}