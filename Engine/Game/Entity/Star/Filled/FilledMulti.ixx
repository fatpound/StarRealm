module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.FilledBase;
import StarRealm.Entity.Star.MultiColorBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class FilledMulti final : public StarBase<FilledBase, MultiColorBase>
    {
    public:
        FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}