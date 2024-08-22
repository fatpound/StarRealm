module;

#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

#include <cassert>

module FatPound.Win32.D3D11.Visual.Drawable;

namespace fatpound::win32::d3d11::visual
{
    void Drawable::Draw(ID3D11DeviceContext* const pImmediateContext) const noexcept(IN_RELEASE)
    {
        for (auto& bindable : m_binds_)
        {
            bindable->Bind(pImmediateContext);
        }

        for (auto& static_bindable : this->GetStaticBinds_())
        {
            static_bindable->Bind(pImmediateContext);
        }

        pImmediateContext->DrawIndexed(pCIndexBuffer_->GetCount(), 0u, 0);
    }

    void Drawable::AddBind_(std::unique_ptr<NAMESPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)
    {
        assert((typeid(*bind) != typeid(NAMESPACE_PIPELINE_ELEMENT::IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

        m_binds_.push_back(std::move(bind));
    }

    void Drawable::AddIndexBuffer_(std::unique_ptr<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE)
    {
        assert((pCIndexBuffer_ == nullptr) && "Attempting to add index buffer a second time");

        pCIndexBuffer_ = idxbuf.get();

        m_binds_.push_back(std::move(idxbuf));
    }
}