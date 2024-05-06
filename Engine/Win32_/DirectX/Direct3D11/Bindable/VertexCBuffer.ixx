module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module VertexCBuffer;

import D3D11Graphics;
import CBuffer;
import Bindable;

export namespace fatpound::win32::d3d11
{
    template <typename C>
    class VertexCBuffer final : public CBuffer<C>
    {
    public:
        using CBuffer<C>::CBuffer;

        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->VSSetConstantBuffers(0u, 1u, this->pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}