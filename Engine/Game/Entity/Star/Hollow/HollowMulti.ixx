module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.HollowMulti;

import StarRealm.Entity.Star.Base;
import StarRealm.Entity.Star.HollowBase;
import StarRealm.Entity.Star.MultiColorBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class HollowMulti final : public StarBase<HollowBase, MultiColorBase>
    {
    public:
        HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}