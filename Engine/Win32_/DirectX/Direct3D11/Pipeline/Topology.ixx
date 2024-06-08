module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

export module Direct3D11.Pipeline.Topology;

import Direct3D11.Graphics;
import Direct3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline
{
    class Topology final : public Bindable
    {
    public:
        Topology(D3D11_PRIMITIVE_TOPOLOGY type);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY type_;


    private:
    };
}