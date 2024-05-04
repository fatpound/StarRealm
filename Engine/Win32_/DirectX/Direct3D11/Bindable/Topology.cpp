module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

module Topology;

namespace fatpound::win32::d3d11
{
    Topology::Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
        :
        type_(type)
    {

    }

    void Topology::Bind(Graphics& gfx) noexcept
    {
        GetContext_(gfx)->IASetPrimitiveTopology(type_);
    }
}