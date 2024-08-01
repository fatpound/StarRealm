module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.HollowBase;
import StarRealm.Entity.Star.Style.Effect.SingleColorBase;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowSingle final : public StarBase<HollowBase, SingleColorBase>
    {
    public:
        HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}