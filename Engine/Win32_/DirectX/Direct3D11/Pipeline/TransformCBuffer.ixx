module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module Direct3D11.Pipeline.TransformCBuffer;

import Direct3D11.Graphics;
import Direct3D11.Pipeline.VertexCBuffer;
import Direct3D11.Pipeline.Bindable;
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