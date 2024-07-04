module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.HollowBase;
import StarRealm.Entity.Star.Style.Effect.BlendBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class HollowBlend final : public StarBase<HollowBase, BlendBase>
    {
    public:
        HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}