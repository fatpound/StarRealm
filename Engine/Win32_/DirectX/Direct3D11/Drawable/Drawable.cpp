module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <cassert>

module Drawable;

namespace fatpound::win32::d3d11
{
    void Drawable::Draw(Graphics& gfx) const noexcept(IN_RELEASE)
    {
        for (auto& bindable : binds_)
        {
            bindable->Bind(gfx);
        }

        for (auto& bindable : GetStaticBinds_())
        {
            bindable->Bind(gfx);
        }

        gfx.DrawIndexed(pCIndexBuffer_->GetCount());
    }

    void Drawable::AddBind_(std::unique_ptr<pipeline::Bindable> bind) noexcept(IN_RELEASE)
    {
        assert((typeid(*bind) != typeid(pipeline::IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

        binds_.push_back(std::move(bind));
    }

    void Drawable::AddIndexBuffer_(std::unique_ptr<pipeline::IndexBuffer> idxbuf) noexcept(IN_RELEASE)
    {
        assert((pCIndexBuffer_ == nullptr) && "Attempting to add index buffer a second time");

        pCIndexBuffer_ = idxbuf.get();

        binds_.push_back(std::move(idxbuf));
    }
}