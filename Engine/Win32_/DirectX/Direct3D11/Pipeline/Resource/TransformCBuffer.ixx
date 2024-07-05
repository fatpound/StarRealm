module;

#include "../../../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:TransformCBuffer;

import :VertexCBuffer;
import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <class C>
    class TransformCBuffer final : public Bindable
    {
    public:
        TransformCBuffer(Graphics& gfx, const C& parent)
            :
            vcbuf_(gfx),
            parent_(parent)
        {

        }


    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            vcbuf_.Update(
                gfx,
                DirectX::XMMatrixTranspose(
                    parent_.GetTransformXM() *
                    gfx.GetCameraXM() *
                    gfx.GetProjectionXM()
                )
            );

            vcbuf_.Bind(gfx);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> vcbuf_;

        const C& parent_;
    };
}