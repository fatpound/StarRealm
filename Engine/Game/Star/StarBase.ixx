module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module StarBase;

import Bindable;
import Drawable;
import Star;

#if (_MSVC_LANG > 202002L)
import std;
#else
#if (_MSVC_LANG == 202002L)
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
#endif // (_MSVC_LANG == 202002L)
#endif // (_MSVC_LANG > 202002L)

export namespace fatpound::starrealm
{
    template <class C>
    class StarBase : public Star
    {
    public:
        using Star::Star;


    protected:
        virtual bool IsStaticInitialized_() const noexcept(!IS_DEBUG) override final
        {
            return !static_binds_.empty();
        }

        virtual void AddStaticBind_(std::unique_ptr<fatpound::win32::d3d11::Bindable> bind) noexcept(!IS_DEBUG) override final
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(fatpound::win32::d3d11::IndexBuffer));

            static_binds_.push_back(std::move(bind));
        }
        virtual void AddStaticIndexBuffer_(std::unique_ptr<fatpound::win32::d3d11::IndexBuffer> ibuf) noexcept(!IS_DEBUG) override final
        {
            assert(pCIndexBuffer_ == nullptr);

            pCIndexBuffer_ = ibuf.get();

            static_binds_.push_back(std::move(ibuf));
        }
        virtual void SetIndexFromStatic_() noexcept(!IS_DEBUG) override final
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            for (const auto& b : static_binds_)
            {
                if (const auto p = dynamic_cast<fatpound::win32::d3d11::IndexBuffer*>(b.get()))
                {
                    pCIndexBuffer_ = p;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && pCIndexBuffer_ != nullptr);
        }


    protected:


    private:
        virtual const std::vector<std::unique_ptr<fatpound::win32::d3d11::Bindable>>& GetStaticBinds_() const noexcept(!IS_DEBUG) override final
        {
            return static_binds_;
        }


    private:
        static std::vector<std::unique_ptr<fatpound::win32::d3d11::Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<fatpound::win32::d3d11::Bindable>> StarBase<C>::static_binds_;
}