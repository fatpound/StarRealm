module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledBlend;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledBlend::FilledBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView)
        :
        StarBase<style::type::Filled, style::effect::Blend>(gfx, desc, worldView)
    {
        const auto& vertices = STARREALM_STAR_EFFECT::Blend::GenerateVertices(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

        const auto& indices = STARREALM_STAR_TYPE::Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx.GetDevice(), indices));
    }
}
