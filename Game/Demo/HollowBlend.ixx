module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class HollowBlend final : public entity::StarBase<STARREALM_STAR_TYPE::Hollow, STARREALM_STAR_EFFECT::Blend>
    {
    public:
        explicit HollowBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = STARREALM_STAR_EFFECT::Blend::GenerateVertices<false>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_STAR_TYPE::Hollow::GenerateIndices<>(vertices.size())
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
