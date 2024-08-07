module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.FilledBase;
import StarRealm.Entity.Star.Style.Effect.MultiColorBase;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledMulti final : public StarBase<FilledBase, MultiColorBase>
    {
    public:
        FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        FilledMulti() = delete;
        FilledMulti(const FilledMulti& src) = delete;
        FilledMulti& operator = (const FilledMulti& src) = delete;

        FilledMulti(FilledMulti&& src) = delete;
        FilledMulti& operator = (FilledMulti&& src) = delete;
        virtual ~FilledMulti() = default;


    protected:


    private:
    };
}