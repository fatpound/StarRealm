module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarFilledBlend;

import Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarFilledBlend final : public StarBase<StarFilledBlend>
    {
    public:
        StarFilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}