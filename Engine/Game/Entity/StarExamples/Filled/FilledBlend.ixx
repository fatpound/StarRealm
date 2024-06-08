module;

#include "../../../../Win32_/FatWin32_.hpp"

export module StarRealm.Entity.FilledBlend;

import StarRealm.Entity.StarBase;

import FatPound.Win32.Direct3D11.Graphics;

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