module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Pipeline.Bindable;

import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline
{
    class Bindable
    {
    public:
        explicit Bindable() = default;
        explicit Bindable(const Bindable& src) = default;
        explicit Bindable(Bindable&& src) = default;

        Bindable& operator = (const Bindable& src) = default;
        Bindable& operator = (Bindable&& src) = default;
        virtual ~Bindable() noexcept = default;
        

    public:
        virtual void Bind(Graphics& gfx) noexcept = 0;


    protected:
        static auto GetDevice_(Graphics& gfx)  noexcept -> ID3D11Device*;
        static auto GetContext_(Graphics& gfx) noexcept -> ID3D11DeviceContext*;


    private:
    };
}