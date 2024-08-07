module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.HollowBase;
import StarRealm.Entity.Star.Style.Effect.MultiColorBase;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowMulti final : public StarBase<HollowBase, MultiColorBase>
    {
    public:
        HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        HollowMulti() = delete;
        HollowMulti(const HollowMulti& src) = delete;
        HollowMulti& operator = (const HollowMulti& src) = delete;

        HollowMulti(HollowMulti&& src) = delete;
        HollowMulti& operator = (HollowMulti&& src) = delete;
        virtual ~HollowMulti() = default;


    protected:


    private:
    };
}