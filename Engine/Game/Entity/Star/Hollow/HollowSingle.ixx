module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.HollowSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.HollowBase;
import StarRealm.Entity.Star.SingleColorBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class HollowSingle final : public StarBase<HollowBase, SingleColorBase>
    {
    public:
        HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}