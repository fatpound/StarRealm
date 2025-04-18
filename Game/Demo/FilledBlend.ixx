module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.FilledBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class FilledBlend final : public entity::StarBase<STARREALM_ENTITY_FILL::Filled, STARREALM_ENTITY_COLOR::Blend>
    {
    public:
        explicit FilledBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = STARREALM_ENTITY_COLOR::Blend::GenerateVertices<>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_FILL::Filled::GenerateIndices<>(vertices)
                )
            );
        }

        explicit FilledBlend()                       = delete;
        explicit FilledBlend(const FilledBlend&)     = delete;
        explicit FilledBlend(FilledBlend&&) noexcept = delete;

        auto operator = (const FilledBlend&)     -> FilledBlend& = delete;
        auto operator = (FilledBlend&&) noexcept -> FilledBlend& = delete;
        virtual ~FilledBlend() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
