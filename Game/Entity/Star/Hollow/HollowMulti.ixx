module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.HollowMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowMulti final : public StarBase<style::type::Hollow, style::effect::MultiColor>
    {
    public:
        explicit HollowMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_STAR_TYPE::Hollow::GenerateIndices<unsigned short int>(vertices.size())
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
