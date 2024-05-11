module;

#include "../../../FatWin32_.hpp"

export module Bindable;

import D3D11Graphics;

export namespace fatpound::win32::d3d11
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