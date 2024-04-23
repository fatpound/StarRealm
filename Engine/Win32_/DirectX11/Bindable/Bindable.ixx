module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>

export module Bindable;

import D3D11Graphics;

export namespace fatpound::starrealm
{
    class Bindable
    {
    public:
        virtual ~Bindable() = default;


    public:
        virtual void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept = 0;


    protected:
        static ID3D11Device* GetDevice_(fatpound::dx11::D3DGraphics& gfx) noexcept;
        static ID3D11DeviceContext* GetContext_(fatpound::dx11::D3DGraphics& gfx) noexcept;


    private:
    };
}