module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.FilledMulti;

import FatPound.Win32.Direct3D11.Graphics;
import StarBase;

export namespace fatpound::starrealm::entity
{
    class FilledMulti final : public StarBase<FilledMulti>
    {
    public:
        FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}