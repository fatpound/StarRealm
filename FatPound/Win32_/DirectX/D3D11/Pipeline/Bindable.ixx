module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Bindable;

export import FatPound.Win32.D3D11.Graphics.DevicePack;

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
        virtual void Bind(GfxDevicePack& gfx_devicePack) = 0;


    protected:


    private:
    };
}