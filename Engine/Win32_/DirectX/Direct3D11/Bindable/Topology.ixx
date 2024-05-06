module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

export module Topology;

import D3D11Graphics;
import Bindable;

export namespace fatpound::win32::d3d11
{
    class Topology final : public Bindable
    {
    public:
        Topology(Graphics& gfx, D3D11_PRIMITIVE_TOPOLOGY type);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY type_;


    private:
    };
}