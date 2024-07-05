module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.FilledBlend;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    FilledBlend::FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<FilledBase, BlendBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            FilledBase::Init<StarBase>();
            BlendBase::Init<StarBase>(gfx);
        }

        const auto& vertices = BlendBase::GenerateVertices(radiuses_, position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        const auto& indices = FilledBase::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::TransformCBuffer>(gfx, *this));
    }
}