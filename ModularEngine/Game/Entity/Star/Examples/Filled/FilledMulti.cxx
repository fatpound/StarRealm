module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledMulti::FilledMulti(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Filled, style::effect::MultiColor>(gfx, desc)
    {
        const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx.GetDevice(), vertices));

        const auto& indices = NAMESPACE_STAR_TYPE::Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx.GetDevice(), indices));

        const auto& sbuf = NAMESPACE_STAR_EFFECT::MultiColor::ColorBase_::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelSBuffer<NAMESPACE_STAR_EFFECT::MultiColor::ColorBase_::SBuffer::Type>>(gfx.GetDevice(), gfx.GetImmediateContext(), sbuf.vertex_colors));
    }
}