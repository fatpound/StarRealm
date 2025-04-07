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
        explicit HollowMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView);

        explicit HollowMulti()                       = delete;
        explicit HollowMulti(const HollowMulti&)     = delete;
        explicit HollowMulti(HollowMulti&&) noexcept = delete;

        auto operator = (const HollowMulti&)     -> HollowMulti& = delete;
        auto operator = (HollowMulti&&) noexcept -> HollowMulti& = delete;
        virtual ~HollowMulti() noexcept final                    = default;


    protected:


    private:
    };
}

module : private;
