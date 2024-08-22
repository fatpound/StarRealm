module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

module FatPound.Win32.D3D11.Pipeline.Element:Topology;

namespace fatpound::win32::d3d11::pipeline::element
{
    Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type) noexcept
        :
        m_type_(type)
    {

    }

    void Topology::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->IASetPrimitiveTopology(m_type_);
    }
}