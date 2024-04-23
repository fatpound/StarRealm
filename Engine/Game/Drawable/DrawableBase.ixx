module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module DrawableBase;

import Bindable;
import Drawable;

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

export namespace fatpound::starrealm
{
    template <class C>
    class DrawableBase : public Drawable
    {
    public:


    protected:
        virtual bool IsStaticInitialized_() const noexcept = 0;

        virtual void AddStaticBind_(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) = 0;
        virtual void AddStaticIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) = 0;
        virtual void SetIndexFromStatic_() = 0;


    protected:


    private:
        static std::vector<std::unique_ptr<Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<Bindable>> DrawableBase<C>::static_binds_;
}