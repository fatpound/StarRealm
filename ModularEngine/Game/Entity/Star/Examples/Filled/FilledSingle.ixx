module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.FilledSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.FilledBase;
import StarRealm.Entity.Star.Style.Effect.SingleColorBase;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledSingle final : public StarBase<FilledBase, SingleColorBase>
    {
    public:
        FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}