module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>

export module TransformCBuffer;

import D3D11Graphics;
import VertexCBuffer;
import Bindable;
import Drawable;

export namespace fatpound::starrealm
{
    class TransformCBuffer : public Bindable
    {
    public:
        TransformCBuffer(fatpound::dx11::D3DGraphics& gfx, const Drawable& parent);


    public:
        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> vcbuf_;

        const Drawable& parent_;
    };
}