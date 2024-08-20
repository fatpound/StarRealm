module;

#include <FatWin32_Namespaces.hpp>

#include <cassert>

export module FatPound.Win32.D3D11.Visual.DrawableBase;

import FatPound.Win32.D3D11.Visual.Drawable;
import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::win32::d3d11::visual
{
    template <typename T>
    class DrawableBase : public Drawable, public NAMESPACE_PIPELINE::StaticBindableVec<DrawableBase<T>>
    {
    public:
        explicit DrawableBase() = default;
        explicit DrawableBase(const DrawableBase& src) = delete;
        explicit DrawableBase(DrawableBase&& src) = delete;

        DrawableBase& operator = (const DrawableBase& src) = delete;
        DrawableBase& operator = (DrawableBase&& src) = delete;
        virtual ~DrawableBase() noexcept = default;


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            pCIndexBuffer_ = idxbuf.get();

            this->m_static_binds_.push_back(std::move(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            for (const auto& b : this->m_static_binds_)
            {
                const auto ptr = dynamic_cast<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer*>(b.get());

                if (ptr != nullptr)
                {
                    pCIndexBuffer_ = ptr;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && pCIndexBuffer_ != nullptr);
        }


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>>& override
        {
            return this->m_static_binds_;
        }
    };
}