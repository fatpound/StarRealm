module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowBlend;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowBlend::HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Hollow, style::effect::Blend>(gfx, desc)
    {
        const auto& vertices = NAMESPACE_STAR_EFFECT::Blend::GenerateVertices<false>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = NAMESPACE_STAR_TYPE::Hollow::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));
    }
}