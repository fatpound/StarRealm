module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>
#include <wrl.h>

module TransformCBuffer;

namespace fatpound::win32::d3d11::pipeline
{
    TransformCBuffer::TransformCBuffer(D3D11_NAMESPACE::Graphics& gfx, const D3D11_NAMESPACE::Drawable& parent)
        :
        vcbuf_(gfx),
        parent_(parent)
    {

    }

    void TransformCBuffer::Bind(D3D11_NAMESPACE::Graphics& gfx) noexcept
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
}