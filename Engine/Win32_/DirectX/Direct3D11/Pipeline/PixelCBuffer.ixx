module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module PixelCBuffer;

import D3D11Graphics;
import CBuffer;
import Bindable;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename C>
    class PixelCBuffer final : public CBuffer<C>
    {
        using CBuffer<C>::CBuffer;

    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->PSSetConstantBuffers(0u, 1u, this->pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}