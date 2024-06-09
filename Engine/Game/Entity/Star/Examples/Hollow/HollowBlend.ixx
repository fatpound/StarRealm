module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.HollowBlend;

import StarRealm.Entity.Star.Base;

import FatPound.Win32;

export namespace fatpound::starrealm::entity
{
    class HollowBlend final : public StarBase<HollowBlend>
    {
    public:
        HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}