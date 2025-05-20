module;

#include <FatNamespaces.hxx>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class FilledMulti final : public entity::StarBase<STARREALM_ENTITY_FILL::Filled, STARREALM_ENTITY_COLOR::Multi>
    {
    public:
        explicit FilledMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_FILL::Filled::GenerateIndices<>(vertices)
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

        explicit FilledMulti()                       = delete;
        explicit FilledMulti(const FilledMulti&)     = delete;
        explicit FilledMulti(FilledMulti&&) noexcept = delete;

        auto operator = (const FilledMulti&)     -> FilledMulti& = delete;
        auto operator = (FilledMulti&&) noexcept -> FilledMulti& = delete;
        virtual ~FilledMulti() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
