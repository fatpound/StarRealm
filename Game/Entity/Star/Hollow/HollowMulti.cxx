module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowMulti::HollowMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
        :
        StarBase<style::type::Hollow, style::effect::MultiColor>(gfx, desc, worldView)
    {
        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

        const auto& indices = STARREALM_STAR_TYPE::Hollow::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx.GetDevice(), indices));
        
        const auto& sbuf = STARREALM_STAR_EFFECT::MultiColor::ColorBase_::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<FATSPACE_PIPELINE_RESOURCE::PixelSBuffer<STARREALM_STAR_EFFECT::MultiColor::ColorBase_::SBuffer::Type>>(gfx.GetDevice(), gfx.GetImmediateContext(), sbuf.vertex_colors));
    }
}