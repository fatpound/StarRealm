module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Pipeline.Element:Topology;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class Topology final : public Bindable
    {
    public:
        explicit Topology(D3D11_PRIMITIVE_TOPOLOGY type) noexcept;

        explicit Topology() = delete;
        explicit Topology(const Topology& src) = delete;
        explicit Topology(Topology&& src) = delete;

        Topology& operator = (const Topology& src) = delete;
        Topology& operator = (Topology&& src) = delete;
        virtual ~Topology() noexcept final = default;


    public:
        virtual void Bind(Graphics& gfx) override final;


    protected:
        D3D11_PRIMITIVE_TOPOLOGY m_type_;


    private:
    };
}