module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module DrawableBase;

import Bindable;
import Drawable;

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
        virtual bool IsStaticInitialized_() const noexcept(IN_RELEASE) = 0;

        virtual void AddStaticBind_(std::unique_ptr<Bindable> bind) noexcept(IN_RELEASE) = 0;
        virtual void AddStaticIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) noexcept(IN_RELEASE) = 0;
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) = 0;


    protected:


    private:
        static std::vector<std::unique_ptr<Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<Bindable>> DrawableBase<C>::static_binds_;
}