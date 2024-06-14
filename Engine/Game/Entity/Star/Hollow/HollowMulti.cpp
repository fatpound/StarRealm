module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.HollowMulti;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    HollowMulti::HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, MultiColorBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            HollowBase::Init<StarBase>();
            MultiColorBase::Init<StarBase>(gfx);
        }

        const auto& vertices = Star::Make(radius_, position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));
        
        const auto& sbuf = MultiColorBase::ColorBase::GeneratePixelSBuffer(desc.flare_count);

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::PixelSBuffer<MultiColorBase::ColorBase::SBuffer::Type>>(gfx, sbuf.vertex_colors));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}