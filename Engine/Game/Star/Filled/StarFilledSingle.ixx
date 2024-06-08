module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarFilledSingle;

import FatPound.Win32.Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm
{
    class StarFilledSingle final : public StarBase<StarFilledSingle>
    {
    public:
        StarFilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}