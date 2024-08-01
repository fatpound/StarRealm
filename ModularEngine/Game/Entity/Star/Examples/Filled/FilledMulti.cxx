module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.FilledMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledMulti::FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<FilledBase, MultiColorBase>(gfx, desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            FilledBase::Init<StarBase>();
            MultiColorBase::Init<StarBase>(gfx);
        }

        const auto& vertices = Star::Make<true>(radiuses_, position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = FilledBase::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& sbuf = MultiColorBase::ColorBase::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelSBuffer<MultiColorBase::ColorBase::SBuffer::Type>>(gfx, sbuf.vertex_colors));
    }
}