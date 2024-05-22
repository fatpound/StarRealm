module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowSingle;

import D3D11Graphics;
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