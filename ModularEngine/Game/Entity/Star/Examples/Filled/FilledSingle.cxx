module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledSingle::FilledSingle(NAMESPACE_D3D11::Graphics<>& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Filled, style::effect::SingleColor>(gfx, desc)
    {
        const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = NAMESPACE_STAR_TYPE::Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& cbuf = NAMESPACE_STAR_EFFECT::SingleColor::ColorBase_::GeneratePixelCBuffer();
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelCBuffer<NAMESPACE_STAR_EFFECT::SingleColor::ColorBase_::CBuffer>>(gfx, cbuf));
    }
}