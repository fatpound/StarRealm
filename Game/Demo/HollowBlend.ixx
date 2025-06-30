module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class HollowBlend final : public entity::StarBase<STARREALM_ENTITY_FILL::Hollow, STARREALM_ENTITY_COLOR::Blend>
    {
    public:
        explicit HollowBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = STARREALM_ENTITY_COLOR::Blend::GenerateVertices<false>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_D3D11::pipeline::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_D3D11::pipeline::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_FILL::Hollow::GenerateIndices<>(vertices.size())
                )
            );
        }

        explicit HollowBlend()                       = delete;
        explicit HollowBlend(const HollowBlend&)     = delete;
        explicit HollowBlend(HollowBlend&&) noexcept = delete;

        auto operator = (const HollowBlend&)     -> HollowBlend& = delete;
        auto operator = (HollowBlend&&) noexcept -> HollowBlend& = delete;
        virtual ~HollowBlend() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
