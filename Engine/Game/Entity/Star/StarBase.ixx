module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.StarBase;

import StarRealm.Entity.Star;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::entity::star
{
    template <Type T, Effect E>
    class StarBase : public Star
    {
        friend T;
        friend E;

    public:
        StarBase(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
            :
            Star(desc)
        {
            AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::TransformCBuffer<StarBase>>(gfx, *this));
        }


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


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>>& override final
        {
            return static_binds_;
        }


    private:
        inline static std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> static_binds_ = {};
    };
}