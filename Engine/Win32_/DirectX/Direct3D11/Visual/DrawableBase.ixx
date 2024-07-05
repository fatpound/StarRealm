module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module FatPound.Win32.D3D11.Visual.DrawableBase;

import FatPound.Win32.D3D11.Visual.Drawable;
import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::win32::d3d11::visual
{
    template <class C>
    class DrawableBase : public Drawable
    {
    public:


    protected:
        static bool IsStaticInitialized_() noexcept(IN_RELEASE)
        {
            return not static_binds_.empty();
        }

        static void AddStaticBind_(std::unique_ptr<NAMESPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(NAMESPACE_PIPELINE::IndexBuffer));

            static_binds_.push_back(std::move(bind));
        }


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<NAMESPACE_PIPELINE::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            pCIndexBuffer_ = idxbuf.get();

            static_binds_.push_back(std::move(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            for (const auto& b : static_binds_)
            {
                const auto ptr = dynamic_cast<NAMESPACE_PIPELINE::IndexBuffer*>(b.get());

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
            return static_binds_;
        }


    private:
        inline static std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> static_binds_ = {};
    };
}