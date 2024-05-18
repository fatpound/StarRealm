module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

export module Topology;

import D3D11Graphics;
import Bindable;

export namespace fatpound::win32::d3d11::pipeline
{
    class Topology final : public Bindable
    {
    public:
        Topology(D3D11_PRIMITIVE_TOPOLOGY type);


    public:
        virtual void Bind(NAMESPACE_D3D11::Graphics& gfx) noexcept override final;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY type_;


    private:
    };
}