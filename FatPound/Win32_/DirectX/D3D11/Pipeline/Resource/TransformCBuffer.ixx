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
        explicit TransformCBuffer(ID3D11Device* pDevice, const C& parent, Graphics<>& gfx)
            :
            m_vcbuf_(pDevice),
            m_parent_(parent)
        {
            s_pGfx_ = std::addressof(gfx);
        }

        explicit TransformCBuffer() = delete;
        explicit TransformCBuffer(const TransformCBuffer& src) = delete;
        explicit TransformCBuffer(TransformCBuffer&& src) = delete;

        TransformCBuffer& operator = (const TransformCBuffer& src) = delete;
        TransformCBuffer& operator = (TransformCBuffer&& src) = delete;
        virtual ~TransformCBuffer() noexcept final = default;


    public:
        virtual void Bind([[maybe_unused]] ID3D11Device* pDevice, [[maybe_unused]] ID3D11DeviceContext* pImmediateContext) override final
        {
            m_vcbuf_.Update(
                pImmediateContext,
                ::DirectX::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    s_pGfx_->GetCameraXM() *
                    s_pGfx_->GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pDevice, pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> m_vcbuf_;

        const C& m_parent_;

        inline static Graphics<>* s_pGfx_{};
    };
}