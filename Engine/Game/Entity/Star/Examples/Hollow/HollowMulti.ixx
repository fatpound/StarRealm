module;

#include "../../../../../Win32_/FatWin32_.hpp"

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


    protected:


    private:
    };
}