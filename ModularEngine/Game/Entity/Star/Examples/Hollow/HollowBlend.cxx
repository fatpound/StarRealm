module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowBlend;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowBlend::HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, BlendBase>(gfx, desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            HollowBase::Init<StarBase>();
            BlendBase::Init<StarBase>(gfx);
        }

        const auto& vertices = BlendBase::GenerateVertices<false>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));
    }
}