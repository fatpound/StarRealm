module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledSingle;

import StarRealm.Entity.Star.Base;
import StarRealm.Entity.Star.FilledBase;
import StarRealm.Entity.Star.SingleColorBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class FilledSingle final : public StarBase<FilledBase, SingleColorBase>
    {
    public:
        FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}