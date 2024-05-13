module;

#include "../../../FatWin32_.hpp"

module Topology;

namespace fatpound::win32::d3d11
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