module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

module TransformCBuffer;

namespace fatpound::win32::d3d11
{
    TransformCBuffer::TransformCBuffer(Graphics& gfx, const Drawable& parent)
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