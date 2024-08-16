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
    class StarBase : public Star
    {
        friend T;
        friend E;

    public:
        explicit StarBase(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
            :
            Star(desc)
        {
            if (not IsStaticInitialized_())
            {
                T::template Init<StarBase<T, E>>();

                if constexpr (std::derived_from<E, style::effect::Blend>)
                {
                    E::template Init<StarBase<T, E>>(gfx);
                }
                else
                {
                    E::template Init<StarBase<T, E>, std::same_as<T, style::type::Filled>>(gfx);
                }
            }

            AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::TransformCBuffer<StarBase>>(gfx, *this));
        }

        explicit StarBase() = delete;
        explicit StarBase(const StarBase& src) = delete;
        explicit StarBase(StarBase&& src) = delete;

        StarBase& operator = (const StarBase& src) = delete;
        StarBase& operator = (StarBase&& src) = delete;
        virtual ~StarBase() noexcept = default;


    protected:
        static bool IsStaticInitialized_() noexcept(IN_RELEASE)
        {
            return not m_static_binds_.empty();
        }

        static void AddStaticBind_(std::unique_ptr<NAMESPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE)
        {
            assert("*Must* use AddStaticIndexBuffer to bind index buffer" && typeid(*bind) != typeid(NAMESPACE_PIPELINE_ELEMENT::IndexBuffer));

            m_static_binds_.push_back(std::move(bind));
        }


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>>& override final
        {
            return m_static_binds_;
        }


    private:
        inline static std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> m_static_binds_ = {};
    };
}