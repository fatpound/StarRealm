module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledMulti::FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Filled, style::effect::MultiColor>(gfx, desc)
    {
        using namespace style::type;
        using namespace style::effect;

        if (not StarBase::IsStaticInitialized_())
        {
            Filled::Init<StarBase>();
            MultiColor::Init<StarBase>(gfx);
        }

        const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& sbuf = MultiColor::ColorBase_::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelSBuffer<MultiColor::ColorBase_::SBuffer::Type>>(gfx, sbuf.vertex_colors));
    }
}