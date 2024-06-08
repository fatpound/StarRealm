module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

export module FatPound.Win32.Direct3D11.Pipeline.Bindable;

import FatPound.Win32.Direct3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline
{
    class Bindable
    {
    public:
        virtual ~Bindable() = default;
        

    public:
        virtual void Bind(Graphics& gfx) noexcept = 0;


    protected:
        static ID3D11Device* GetDevice_(Graphics& gfx) noexcept;
        static ID3D11DeviceContext* GetContext_(Graphics& gfx) noexcept;


    private:
    };
}