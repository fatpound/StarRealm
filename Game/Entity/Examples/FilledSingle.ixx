module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Examples.FilledSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity
{
    class FilledSingle final : public StarBase<STARREALM_STAR_TYPE::Filled, STARREALM_STAR_EFFECT::SingleColor>
    {
    public:
        explicit FilledSingle(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_STAR_TYPE::Filled::GenerateIndices<>(vertices)
                )
            );

            AddBind_(
                std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelCBuffer<STARREALM_STAR_EFFECT::SingleColor::ColorBase_::CBuffer>>(
                    gfx.GetDevice(),
                    STARREALM_STAR_EFFECT::SingleColor::ColorBase_::GeneratePixelCBuffer()
                )
            );
        }

        explicit FilledSingle()                        = delete;
        explicit FilledSingle(const FilledSingle&)     = delete;
        explicit FilledSingle(FilledSingle&&) noexcept = delete;

        auto operator = (const FilledSingle&)     -> FilledSingle& = delete;
        auto operator = (FilledSingle&&) noexcept -> FilledSingle& = delete;
        virtual ~FilledSingle() noexcept override final            = default;


    protected:


    private:
    };
}

module : private;
