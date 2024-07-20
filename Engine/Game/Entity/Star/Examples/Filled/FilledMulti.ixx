module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.FilledBase;
import StarRealm.Entity.Star.Style.Effect.MultiColorBase;

import FatPound.Win32;

export namespace starrealm::entity::star
{
    class FilledMulti final : public StarBase<FilledBase, MultiColorBase>
    {
    public:
        FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}