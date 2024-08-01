module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.HollowBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.HollowBase;
import StarRealm.Entity.Star.Style.Effect.BlendBase;

import FatPound;

export namespace starrealm::entity::star
{
    class HollowBlend final : public StarBase<HollowBase, BlendBase>
    {
    public:
        HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        HollowBlend() = delete;
        HollowBlend(const HollowBlend& src) = delete;
        HollowBlend& operator = (const HollowBlend& src) = delete;

        HollowBlend(HollowBlend&& src) = delete;
        HollowBlend& operator = (HollowBlend&& src) = delete;
        virtual ~HollowBlend() = default;


    protected:


    private:
    };
}