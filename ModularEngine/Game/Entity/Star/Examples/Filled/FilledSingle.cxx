module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledSingle::FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<FilledBase, SingleColorBase>(gfx, desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            FilledBase::Init<StarBase>();
            SingleColorBase::Init<StarBase>(gfx);
        }

        const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = FilledBase::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& cbuf = SingleColorBase::ColorBase::GeneratePixelCBuffer();
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelCBuffer<SingleColorBase::ColorBase::CBuffer>>(gfx, cbuf));
    }
}