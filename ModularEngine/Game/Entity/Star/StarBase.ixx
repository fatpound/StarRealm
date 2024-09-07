module;

#include <FatWin32_Namespaces.hpp>

#include <cassert>

export module StarRealm.Entity.StarBase;

import StarRealm.Entity.Star;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::entity::star
{
    template
    <
        style::Type T,
        style::Effect E
    >
    class StarBase : public Star, public NAMESPACE_PIPELINE::StaticBindableVec<StarBase<T, E>>
    {
        friend T;
        friend E;

    public:
        explicit StarBase(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc)
            :
            Star(desc)
        {
            if (not NAMESPACE_PIPELINE::StaticBindableVec<StarBase>::IsStaticInitialized_())
            {
                T::template InitStaticBinds<StarBase>();

                if constexpr (std::derived_from<E, style::effect::Blend>)
                {
                    E::template InitStaticBinds<StarBase>(gfx);
                }
                else
                {
                    E::template InitStaticBinds<StarBase, std::same_as<T, style::type::Filled>>(gfx);
                }
            }

            AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::TransformCBuffer<StarBase>>(gfx.GetDevice(), *this, gfx.GetViewXM()));
        }

        explicit StarBase() = delete;
        explicit StarBase(const StarBase& src) = delete;
        explicit StarBase(StarBase&& src) = delete;

        auto operator = (const StarBase& src) -> StarBase& = delete;
        auto operator = (StarBase&& src)      -> StarBase& = delete;
        virtual ~StarBase() noexcept = default;


    protected:


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const bind_vec_t& override final
        {
            return this->m_static_binds_;
        }
    };
}