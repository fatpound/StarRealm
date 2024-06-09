module;

#include "../../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.Star.FilledBlend;

import StarRealm.Entity.Star.Base;

import FatPound.Win32;

export namespace fatpound::starrealm::entity
{
    class FilledBlend final : public StarBase<FilledBlend>
    {
    public:
        FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}