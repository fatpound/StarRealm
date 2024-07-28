module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.FilledBase;
import StarRealm.Entity.Star.Style.Effect.BlendBase;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledBlend final : public StarBase<FilledBase, BlendBase>
    {
    public:
        FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}