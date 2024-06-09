module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.Star.Base;

import FatPound.Win32;

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