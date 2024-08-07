module;

#include <FatWin32_.hpp>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Pipeline.Element:Topology;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class Topology final : public Bindable
    {
    public:
        Topology(D3D11_PRIMITIVE_TOPOLOGY type);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY m_type_;


    private:
    };
}