module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowSingle::HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, SingleColorBase>(gfx, desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            HollowBase::Init<StarBase>();
            SingleColorBase::Init<StarBase, false>(gfx);
        }

        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& cbuf = SingleColorBase::ColorBase::GeneratePixelCBuffer();
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelCBuffer<SingleColorBase::ColorBase::CBuffer>>(gfx, cbuf));
    }
}