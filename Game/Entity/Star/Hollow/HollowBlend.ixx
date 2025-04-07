module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowBlend final : public StarBase<style::type::Hollow, style::effect::Blend>
    {
    public:
        explicit HollowBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView);

        explicit HollowBlend()                       = delete;
        explicit HollowBlend(const HollowBlend&)     = delete;
        explicit HollowBlend(HollowBlend&&) noexcept = delete;

        auto operator = (const HollowBlend&)     -> HollowBlend& = delete;
        auto operator = (HollowBlend&&) noexcept -> HollowBlend& = delete;
        virtual ~HollowBlend() noexcept final                    = default;


    protected:


    private:
    };
}

module : private;
