module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <StarRealmNamespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowSingle::HollowSingle(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
        :
        StarBase<style::type::Hollow, style::effect::SingleColor>(gfx, desc, worldView)
    {
        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

        const auto& indices = STARREALM_STAR_TYPE::Hollow::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx.GetDevice(), indices));

        const auto& cbuf = STARREALM_STAR_EFFECT::SingleColor::ColorBase_::GeneratePixelCBuffer();
        AddBind_(std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelCBuffer<STARREALM_STAR_EFFECT::SingleColor::ColorBase_::CBuffer>>(gfx.GetDevice(), cbuf));
    }
}