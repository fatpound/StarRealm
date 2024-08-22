module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:TransformCBuffer;

import :VertexCBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Visual.ViewXM;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class TransformCBuffer final : public Bindable
    {
    public:
        explicit TransformCBuffer(ID3D11Device* pDevice, const T& parent, NAMESPACE_VISUAL::ViewXM& viewXM)
            :
            m_vcbuf_(pDevice),
            m_parent_(parent),
            m_viewXM_(viewXM)
        {
            
        }

        explicit TransformCBuffer() = delete;
        explicit TransformCBuffer(const TransformCBuffer& src) = delete;
        explicit TransformCBuffer(TransformCBuffer&& src) = delete;

        TransformCBuffer& operator = (const TransformCBuffer& src) = delete;
        TransformCBuffer& operator = (TransformCBuffer&& src) = delete;
        virtual ~TransformCBuffer() noexcept final = default;


    public:
        auto operator <=> (const TransformCBuffer& rhs) const = delete;
        bool operator ==  (const TransformCBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            m_vcbuf_.Update(
                pImmediateContext,
                ::DirectX::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    m_viewXM_.GetCameraXM() *
                    m_viewXM_.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> m_vcbuf_;

        const T& m_parent_;

        NAMESPACE_VISUAL::ViewXM& m_viewXM_;
    };
}