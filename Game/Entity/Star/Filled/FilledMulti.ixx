module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledMulti final : public StarBase<style::type::Filled, style::effect::MultiColor>
    {
    public:
        explicit FilledMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_STAR_TYPE::Filled::GenerateIndices(vertices)
                )
            );

            AddBind_(
                std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelSBuffer<STARREALM_STAR_EFFECT::MultiColor::ColorBase_::SBuffer::Type>>(
                    gfx.GetDevice(),
                    gfx.GetImmediateContext(),
                    STARREALM_STAR_EFFECT::MultiColor::ColorBase_::GeneratePixelSBuffer(desc.flare_count).vertex_colors
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
