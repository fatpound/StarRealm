module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowMulti::HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, MultiColorBase>(gfx, desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            HollowBase::Init<StarBase>();
            MultiColorBase::Init<StarBase, false>(gfx);
        }

        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));
        
        const auto& sbuf = MultiColorBase::ColorBase::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelSBuffer<MultiColorBase::ColorBase::SBuffer::Type>>(gfx, sbuf.vertex_colors));
    }
}