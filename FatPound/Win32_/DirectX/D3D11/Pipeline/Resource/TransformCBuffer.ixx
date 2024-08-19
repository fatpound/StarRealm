module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:TransformCBuffer;

import :VertexCBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Visual.SceneXMPack;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <class C>
    class TransformCBuffer final : public Bindable
    {
    public:
        explicit TransformCBuffer(ID3D11Device* pDevice, const C& parent, NAMESPACE_VISUAL::SceneXMPack& sceneXMpack)
            :
            m_vcbuf_(pDevice),
            m_parent_(parent),
            m_sceneXMpack_(sceneXMpack)
        {
            
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
                    m_sceneXMpack_.GetCameraXM() *
                    m_sceneXMpack_.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pDevice, pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<DirectX::XMMATRIX> m_vcbuf_;

        const C& m_parent_;

        NAMESPACE_VISUAL::SceneXMPack& m_sceneXMpack_;
    };
}