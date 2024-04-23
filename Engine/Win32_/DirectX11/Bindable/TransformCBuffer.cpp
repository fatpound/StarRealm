module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

module TransformCBuffer;

import D3D11Graphics;
import Drawable;

namespace fatpound::starrealm
{
    TransformCBuffer::TransformCBuffer(fatpound::dx11::D3DGraphics& gfx, const Drawable& parent)
        :
        vcbuf_(gfx),
        parent_(parent)
    {

    }

    void TransformCBuffer::Bind(fatpound::dx11::D3DGraphics& gfx) noexcept
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