module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module PixelCBuffer;

import D3D11Graphics;
import CBuffer;
import Bindable;

export namespace fatpound::starrealm
{
    template <typename C>
    class PixelCBuffer : public CBuffer<C>
    {
    public:
        using CBuffer<C>::CBuffer;

        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override
        {
            Bindable::GetContext_(gfx)->PSSetConstantBuffers(0u, 1u, this->pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}