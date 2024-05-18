module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>
#include <wrl.h>

export module TransformCBuffer;

import D3D11Graphics;
import VertexCBuffer;
import Bindable;
import Drawable;

export namespace fatpound::win32::d3d11::pipeline
{
    class TransformCBuffer final : public Bindable
    {
    public:
        TransformCBuffer(D3D11_NAMESPACE::Graphics& gfx, const D3D11_NAMESPACE::Drawable& parent);


    public:
        virtual void Bind(D3D11_NAMESPACE::Graphics& gfx) noexcept override final;


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> vcbuf_;

        const Drawable& parent_;
    };
}