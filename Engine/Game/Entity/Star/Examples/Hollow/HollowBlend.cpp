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

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_int_distribution<int> rgb_dist(0, 255);

        const auto& flare_count = desc.flare_count;

        std::vector<BlendBase::Vertex> vertices;
        vertices.reserve(flare_count * 2u + 1u);

        for (const auto& vertex : Star::Make(radius_, position_, flare_count))
        {
            vertices.emplace_back(
                vertex,
                fatpound::util::Color(
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    255
                )
            );
        }

        const auto& indices = HollowBase::GenerateIndices(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}