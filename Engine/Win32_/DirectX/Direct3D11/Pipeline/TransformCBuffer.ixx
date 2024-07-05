module;

#include "../../../FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.TransformCBuffer;

import FatPound.Win32.D3D11.Pipeline.VertexCBuffer;
import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Visual.Drawable;
import FatPound.Win32.D3D11.Graphics;

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