module;

#include <FatNamespaces.hxx>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class HollowMulti final : public entity::StarBase<STARREALM_ENTITY_FILL::Hollow, STARREALM_ENTITY_COLOR::Multi>
    {
    public:
        explicit HollowMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
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
                std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelSBuffer<STARREALM_ENTITY_COLOR::Multi::ColoringBase::SBuffer::Type>>(
                    gfx.GetDevice(),
                    gfx.GetImmediateContext(),
                    STARREALM_ENTITY_COLOR::Multi::ColoringBase::GeneratePixelSBuffer(desc.flare_count).vertex_colors
                )
            );
        }

        explicit HollowMulti()                       = delete;
        explicit HollowMulti(const HollowMulti&)     = delete;
        explicit HollowMulti(HollowMulti&&) noexcept = delete;

        auto operator = (const HollowMulti&)     -> HollowMulti& = delete;
        auto operator = (HollowMulti&&) noexcept -> HollowMulti& = delete;
        virtual ~HollowMulti() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
