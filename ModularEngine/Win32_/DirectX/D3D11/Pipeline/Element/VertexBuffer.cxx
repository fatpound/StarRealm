module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Element:VertexBuffer;

namespace fatpound::win32::d3d11::pipeline::element
{
    void VertexBuffer::Bind(Graphics& gfx) noexcept
    {
        constexpr UINT offset = 0u;

        Bindable::GetContext_(gfx)->IASetVertexBuffers(0u, 1u, m_pVertexBuffer_.GetAddressOf(), &m_stride_, &offset);
    }
}