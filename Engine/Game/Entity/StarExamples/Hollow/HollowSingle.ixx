module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.HollowSingle;

import FatPound.Win32.Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm::entity
{
    class HollowSingle final : public StarBase<HollowSingle>
    {
    public:
        HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}