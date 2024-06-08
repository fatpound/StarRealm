module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowBlend;

import FatPound.Win32.Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarHollowBlend final : public StarBase<StarHollowBlend>
    {
    public:
        StarHollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}