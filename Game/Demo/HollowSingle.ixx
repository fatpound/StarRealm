module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class HollowSingle final : public entity::StarBase<STARREALM_ENTITY_FILL::Hollow, STARREALM_ENTITY_COLOR::Single>
    {
    public:
        explicit HollowSingle(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_FILL::Hollow::GenerateIndices<>(vertices.size())
                )
            );

            AddBind_(
                std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelCBuffer<STARREALM_ENTITY_COLOR::Single::ColoringBase::CBuffer>>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_COLOR::Single::ColoringBase::GeneratePixelCBuffer()
                )
            );
        }

        explicit HollowSingle()                        = delete;
        explicit HollowSingle(const HollowSingle&)     = delete;
        explicit HollowSingle(HollowSingle&&) noexcept = delete;

        auto operator = (const HollowSingle&)     -> HollowSingle& = delete;
        auto operator = (HollowSingle&&) noexcept -> HollowSingle& = delete;
        virtual ~HollowSingle() noexcept override final            = default;


    protected:


    private:
    };
}

module : private;
