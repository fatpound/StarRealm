module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowBlend final : public StarBase<style::type::Hollow, style::effect::Blend>
    {
    public:
        explicit HollowBlend(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc);

        explicit HollowBlend() = delete;
        explicit HollowBlend(const HollowBlend& src) = delete;
        explicit HollowBlend(HollowBlend&& src) = delete;

        auto operator = (const HollowBlend& src) -> HollowBlend& = delete;
        auto operator = (HollowBlend&& src)      -> HollowBlend& = delete;
        virtual ~HollowBlend() noexcept final = default;


    protected:


    private:
    };
}