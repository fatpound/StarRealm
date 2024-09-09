module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledBlend;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledBlend::FilledBlend(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, NAMESPACE_UTIL::ViewXM& worldView)
        :
        StarBase<style::type::Filled, style::effect::Blend>(gfx, desc, worldView)
    {
        const auto& vertices = NAMESPACE_STAR_EFFECT::Blend::GenerateVertices(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

        const auto& indices = NAMESPACE_STAR_TYPE::Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx.GetDevice(), indices));
    }
}