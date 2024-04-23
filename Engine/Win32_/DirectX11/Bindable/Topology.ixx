module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>

export module Topology;

import D3D11Graphics;
import Bindable;

export namespace fatpound::starrealm
{
    class Topology : public Bindable
    {
    public:
        Topology(fatpound::dx11::D3DGraphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);


    public:
        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY type_;


    private:
    };
}