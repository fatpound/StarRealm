module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

module FatPound.Win32.D3D11.Pipeline:Topology;

namespace fatpound::win32::d3d11::pipeline
{
    Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type)
        :
        type_(type)
    {

    }

    void Topology::Bind(Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->IASetPrimitiveTopology(type_);
    }
}