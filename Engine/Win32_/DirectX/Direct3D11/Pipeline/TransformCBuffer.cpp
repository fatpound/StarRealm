module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>
#include <wrl.h>

module TransformCBuffer;

namespace fatpound::win32::d3d11::pipeline
{
    TransformCBuffer::TransformCBuffer(NAMESPACE_D3D11::Graphics& gfx, const NAMESPACE_ENTITY::Drawable& parent)
        :
        vcbuf_(gfx),
        parent_(parent)
    {

    }

    void TransformCBuffer::Bind(NAMESPACE_D3D11::Graphics& gfx) noexcept
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