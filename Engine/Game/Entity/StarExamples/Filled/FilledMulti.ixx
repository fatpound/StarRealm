module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.FilledMulti;

import StarRealm.Entity.StarBase;

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