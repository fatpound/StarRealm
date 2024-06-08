module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module Direct3D11.Pipeline.VertexCBuffer;

import Direct3D11.Graphics;
import Direct3D11.Pipeline.CBuffer;
import Direct3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename C>
    class VertexCBuffer final : public CBuffer<C>
    {
        using CBuffer<C>::CBuffer;

    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->VSSetConstantBuffers(0u, 1u, this->pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}