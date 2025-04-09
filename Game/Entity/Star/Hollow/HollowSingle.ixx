module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.HollowSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowSingle final : public StarBase<style::type::Hollow, style::effect::SingleColor>
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
                    STARREALM_STAR_TYPE::Hollow::GenerateIndices<unsigned short int>(vertices.size())
                )
            );

            AddBind_(
                std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelCBuffer<STARREALM_STAR_EFFECT::SingleColor::ColorBase_::CBuffer>>(
                    gfx.GetDevice(),
                    STARREALM_STAR_EFFECT::SingleColor::ColorBase_::GeneratePixelCBuffer()
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
