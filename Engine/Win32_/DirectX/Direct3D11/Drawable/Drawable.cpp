module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <cassert>

module Drawable;

namespace fatpound::win32::d3d11
{
    void Drawable::Draw(Graphics& gfx) const noexcept(!IS_DEBUG)
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

    void Drawable::AddBind_(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG)
    {
        assert((typeid(*bind) != typeid(IndexBuffer)) && "*Must* use AddIndexBuffer_() method to bind it!");

        binds_.push_back(std::move(bind));
    }

    void Drawable::AddIndexBuffer_(std::unique_ptr<IndexBuffer> idxbuf) noexcept(!IS_DEBUG)
    {
        assert((pCIndexBuffer_ == nullptr) && "*Must* use AddIndexBuffer_() method to bind it!");

        pCIndexBuffer_ = idxbuf.get();

        binds_.push_back(std::move(idxbuf));
    }
}