module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowSingle;

import FatPound.Win32.Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarHollowSingle final : public StarBase<StarHollowSingle>
    {
    public:
        StarHollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}