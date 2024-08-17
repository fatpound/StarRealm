module;

#include <FatWin32_Settings.hpp>

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
        explicit TransformCBuffer(Graphics& gfx, const C& parent)
            :
            m_vcbuf_(gfx),
            m_parent_(parent)
        {

        }

        explicit TransformCBuffer() = delete;
        explicit TransformCBuffer(const TransformCBuffer& src) = delete;
        explicit TransformCBuffer(TransformCBuffer&& src) = delete;

        TransformCBuffer& operator = (const TransformCBuffer& src) = delete;
        TransformCBuffer& operator = (TransformCBuffer&& src) = delete;
        virtual ~TransformCBuffer() noexcept final = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            m_vcbuf_.Update(
                gfx,
                ::DirectX::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    gfx.GetCameraXM() *
                    gfx.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(gfx);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> m_vcbuf_;

        const C& m_parent_;
    };
}