module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarFilledMulti;

import D3D11Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarFilledMulti final : public StarBase<StarFilledMulti>
    {
    public:
        StarFilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}