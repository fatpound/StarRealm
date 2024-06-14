module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledBlend;

import StarRealm.Entity.Star.Base;
import StarRealm.Entity.Star.FilledBase;
import StarRealm.Entity.Star.BlendBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity::star
{
    class FilledBlend final : public StarBase<FilledBase, BlendBase>
    {
    public:
        FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}