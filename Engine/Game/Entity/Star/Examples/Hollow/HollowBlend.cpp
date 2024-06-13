module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.HollowBlend;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    HollowBlend::HollowBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, BlendBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            HollowBase::Init<StarBase>();
            StarBase::InitBlend(gfx);
        }

        const auto& vertices = BlendBase::GenerateVertices<false>(radius_, position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}