module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

export module FatPound.Win32.D3D11.Pipeline.Bindable;

import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline
{
    class Bindable
    {
    public:
        virtual ~Bindable() noexcept = default;
        

    public:
        virtual void Bind(Graphics& gfx) noexcept = 0;


    protected:
        static auto GetDevice_(Graphics& gfx)  noexcept -> ID3D11Device*;
        static auto GetContext_(Graphics& gfx) noexcept -> ID3D11DeviceContext*;


    private:
    };
}