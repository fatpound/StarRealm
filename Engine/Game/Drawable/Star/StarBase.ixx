module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module StarBase;

import Bindable;
import Drawable;
import Star;

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
    class StarBase : public Star
    {
    public:
        using Star::Star;


    protected:
        bool IsStaticInitialized_() const noexcept override
        {
            return !static_binds_.empty();
        }

        void AddStaticBind_(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG) override
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(IndexBuffer));

            static_binds_.push_back(std::move(bind));
        }
        void AddStaticIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) noexcept(!IS_DEBUG) override
        {
            assert(pCIndexBuffer_ == nullptr);

            pCIndexBuffer_ = ibuf.get();

            static_binds_.push_back(std::move(ibuf));
        }
        void SetIndexFromStatic_() noexcept(!IS_DEBUG) override
        {
            assert("Attempting to add index buffer a second time" && pCIndexBuffer_ == nullptr);

            for (const auto& b : static_binds_)
            {
                if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
                {
                    pCIndexBuffer_ = p;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && pCIndexBuffer_ != nullptr);
        }


    protected:


    private:
        const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds_() const noexcept override
        {
            return static_binds_;
        }


    private:
        static std::vector<std::unique_ptr<Bindable>> static_binds_;
    };

    template <class C>
    std::vector<std::unique_ptr<Bindable>> StarBase<C>::static_binds_;
}