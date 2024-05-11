module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module DrawableBase;

import Bindable;
import Drawable;
import IndexBuffer;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <cmath>;
import <cstdint>;
/**/
import <vector>;
import <memory>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    template <class C>
    class DrawableBase : public Drawable
    {
    public:


    protected:
        static bool IsStaticInitialized_() noexcept(IN_RELEASE)
        {
            return !static_binds_.empty();
        }

        static void AddStaticBind_(std::unique_ptr<Bindable> bind) noexcept(IN_RELEASE)
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(fatpound::win32::d3d11::IndexBuffer));

            static_binds_.push_back(std::move(bind));
        }


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) noexcept(IN_RELEASE)
        {
            assert(pCIndexBuffer_ == nullptr);

            pCIndexBuffer_ = ibuf.get();

            static_binds_.push_back(std::move(ibuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE)
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            for (const auto& b : static_binds_)
            {
                const auto& ptr = dynamic_cast<fatpound::win32::d3d11::IndexBuffer*>(b.get());

                if (ptr != nullptr)
                {
                    pCIndexBuffer_ = ptr;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && pCIndexBuffer_ != nullptr);
        }


    protected:


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<fatpound::win32::d3d11::Bindable>>& override
        {
            return static_binds_;
        }


    private:
        static std::vector<std::unique_ptr<Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<Bindable>> DrawableBase<C>::static_binds_;
}