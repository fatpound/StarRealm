module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.FilledSingle;

import StarRealm.Entity.StarBase;

import FatPound.Win32;

export namespace fatpound::starrealm::entity
{
    class FilledSingle final : public StarBase<FilledSingle>
    {
    public:
        FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}