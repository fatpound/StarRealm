module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

#include <cassert>

export module StarRealm.Entity.StarBase;

import <DirectXMath.h>;

import StarRealm.Entity.Star;
import StarRealm.Entity.Star.Style;
import StarRealm.Entity.DrawableBase;

import FatPound;

import std;

export namespace starrealm::entity
{
    template
    <
        STARREALM_ENTITY_STARSTYLE::Fill  T,
        STARREALM_ENTITY_STARSTYLE::Color U
    >
    class StarBase : public Star
    {
        friend T;
        friend U;

    public:
        explicit StarBase(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            Star(desc)
        {
            if (tl_bindable_vec_.empty())
            {
                T::template InitStaticBinds<StarBase>();

                if constexpr (std::derived_from<U, STARREALM_ENTITY_COLOR::Blend>)
                {
                    U::template InitStaticBinds<StarBase>(gfx);
                }
                else
                {
                    U::template InitStaticBinds<StarBase, std::same_as<T, STARREALM_ENTITY_FILL::Filled>>(gfx);
                }
            }

            const D3D11_BUFFER_DESC tcbd
            {
                .ByteWidth           = sizeof(DirectX::XMMATRIX),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0U,
                .StructureByteStride = 0U
            };

            AddBind_(std::make_unique<FATSPACE_D3D11::pipeline::TransformCBuffer<StarBase>>(gfx.GetDevice(), tcbd, *this, worldView));
        }

        explicit StarBase()                    = delete;
        explicit StarBase(const StarBase&)     = delete;
        explicit StarBase(StarBase&&) noexcept = delete;

        auto operator = (const StarBase&)     -> StarBase& = delete;
        auto operator = (StarBase&&) noexcept -> StarBase& = delete;
        virtual ~StarBase() noexcept override              = default;


    protected:


    private:
        static void AddStaticBind_(BindablePtr_t bindable)
        {
            tl_bindable_vec_.push_back(std::move<>(bindable));
        }


    private:
        virtual auto GetStaticBinds_() const noexcept -> const BindableVec_t& override final
        {
            return tl_bindable_vec_;
        }


    private:
        inline static thread_local std::vector<BindablePtr_t> tl_bindable_vec_;
    };
}

module : private;
