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
            StarBase::InitBlend(gfx);
            StarBase::InitHollow();
        }

        struct Vertex final
        {
            DirectX::XMFLOAT3 pos;

            fatpound::util::Color color;
        };

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_int_distribution<int> rgb_dist(0, 255);

        const auto& flare_count = desc.flare_count;

        std::vector<Vertex> vertices;
        vertices.reserve(flare_count * 2u + 1u);

        for (const auto& vertex : Star::Make(radius_, position_, flare_count))
        {
            vertices.emplace_back(
                vertex,
                fatpound::util::Color(
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    255 // not necessary because we set this Alpha value to 1.0f in the Pixel Shader
                )
            );
        }

        const auto& vertex_count = vertices.size();

        std::vector<unsigned short int> indices;
        indices.reserve(vertex_count + 1u);

        for (std::size_t i = 0u; i < vertex_count; ++i)
        {
            indices.emplace_back(static_cast<unsigned short int>(i));
        }

        indices.emplace_back(static_cast<unsigned short int>(0u));

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}