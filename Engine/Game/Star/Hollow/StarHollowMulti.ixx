module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowMulti;

import Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarHollowMulti final : public StarBase<StarHollowMulti>
    {
    public:
        StarHollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}