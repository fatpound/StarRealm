module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

module TransformCBuffer;

namespace fatpound::win32::d3d11::pipeline
{
    TransformCBuffer::TransformCBuffer(Graphics& gfx, const NAMESPACE_VISUAL::Drawable& parent)
        :
        vcbuf_(gfx),
        parent_(parent)
    {

    }

    void TransformCBuffer::Bind(Graphics& gfx) noexcept
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