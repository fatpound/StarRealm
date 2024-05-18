module;

#include "../../../FatWin32_.hpp"

module Topology;

namespace fatpound::win32::d3d11::pipeline
{
    Topology::Topology(D3D11_PRIMITIVE_TOPOLOGY type)
        :
        type_(type)
    {

    }

    void Topology::Bind(NAMESPACE_D3D11::Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->IASetPrimitiveTopology(type_);
    }
}