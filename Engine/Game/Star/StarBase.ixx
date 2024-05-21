module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module StarBase;

import Bindable;
import Drawable;
import IndexBuffer;
import Star;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
import std.core;
import std.memory;
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::starrealm
{
    template <class C>
    class StarBase : public Star
    {
        using Star::Star;

    public:


    protected:
        static bool IsStaticInitialized_() noexcept(IN_RELEASE)
        {
            return !static_binds_.empty();
        }

        static void AddStaticBind_(std::unique_ptr<NAMESPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(NAMESPACE_PIPELINE::IndexBuffer));

            static_binds_.push_back(std::move(bind));
        }


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>>& override final
        {
            return static_binds_;
        }


    private:
        static std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> StarBase<C>::static_binds_;
}