module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

#include <cassert>

export module StarRealm.Entity.StarBase;

import StarRealm.Entity.Star;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::entity
{
    template
    <
        STARREALM_STAR_STYLE::Type   T,
        STARREALM_STAR_STYLE::Effect E
    >
    class StarBase : public Star
    {
        friend T;
        friend E;

    public:
        explicit StarBase(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            Star(desc)
        {
            if (tl_bindable_vec_.empty())
            {
                T::template InitStaticBinds<StarBase>();

                if constexpr (::std::derived_from<E, STARREALM_STAR_EFFECT::Blend>)
                {
                    E::template InitStaticBinds<StarBase>(gfx);
                }
                else
                {
                    E::template InitStaticBinds<StarBase, ::std::same_as<T, STARREALM_STAR_TYPE::Filled>>(gfx);
                }
            }

            AddBind_(std::make_unique<FATSPACE_PIPELINE_RESOURCE::TransformCBuffer<StarBase>>(gfx.GetDevice(), *this, worldView));
        }

        explicit StarBase()                    = delete;
        explicit StarBase(const StarBase&)     = delete;
        explicit StarBase(StarBase&&) noexcept = delete;

        auto operator = (const StarBase&)     -> StarBase& = delete;
        auto operator = (StarBase&&) noexcept -> StarBase& = delete;
        virtual ~StarBase() noexcept override              = default;


    protected:


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const BindableVec_t& override final
        {
            return tl_bindable_vec_;
        }


    private:
        static void AddStaticBind_(BindablePtr_t bindable)
        {
            tl_bindable_vec_.push_back(std::move(bindable));
        }


    private:
        inline static thread_local std::vector<BindablePtr_t> tl_bindable_vec_;
    };
}

module : private;
