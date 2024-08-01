module;

#include <FatWin32_Namespaces.hpp>

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

        FilledBlend() = delete;
        FilledBlend(const FilledBlend& src) = delete;
        FilledBlend& operator = (const FilledBlend& src) = delete;

        FilledBlend(FilledBlend&& src) = delete;
        FilledBlend& operator = (FilledBlend&& src) = delete;
        virtual ~FilledBlend() = default;


    protected:


    private:
    };
}