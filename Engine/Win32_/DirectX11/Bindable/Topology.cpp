module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>

module Topology;

namespace fatpound::starrealm
{
    Topology::Topology(fatpound::dx11::D3DGraphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type)
        :
        type_(type)
    {

    }

    void Topology::Bind(fatpound::dx11::D3DGraphics& gfx) noexcept
    {
        GetContext_(gfx)->IASetPrimitiveTopology(type_);
    }
}