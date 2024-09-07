module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowSingle final : public StarBase<style::type::Hollow, style::effect::SingleColor>
    {
    public:
        explicit HollowSingle(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc);

        explicit HollowSingle() = delete;
        explicit HollowSingle(const HollowSingle& src) = delete;
        explicit HollowSingle(HollowSingle&& src) = delete;

        auto operator = (const HollowSingle& src) -> HollowSingle& = delete;
        auto operator = (HollowSingle&& src)      -> HollowSingle& = delete;
        virtual ~HollowSingle() noexcept final = default;


    protected:


    private:
    };
}