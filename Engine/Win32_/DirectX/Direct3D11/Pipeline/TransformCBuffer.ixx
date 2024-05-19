module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

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
        TransformCBuffer(Graphics& gfx, const NAMESPACE_VISUAL::Drawable& parent);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> vcbuf_;

        const NAMESPACE_VISUAL::Drawable& parent_;
    };
}