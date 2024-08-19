module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowMulti final : public StarBase<style::type::Hollow, style::effect::MultiColor>
    {
    public:
        explicit HollowMulti(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc);

        explicit HollowMulti() = delete;
        explicit HollowMulti(const HollowMulti& src) = delete;
        explicit HollowMulti(HollowMulti&& src) = delete;

        HollowMulti& operator = (const HollowMulti& src) = delete;
        HollowMulti& operator = (HollowMulti&& src) = delete;
        virtual ~HollowMulti() noexcept final = default;


    protected:


    private:
    };
}