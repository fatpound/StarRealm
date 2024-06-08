module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.HollowMulti;

import StarRealm.Entity.StarBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity
{
    class HollowMulti final : public StarBase<HollowMulti>
    {
    public:
        HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}