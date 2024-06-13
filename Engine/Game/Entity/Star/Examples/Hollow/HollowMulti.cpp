module;

#include "../../../../../Win32_/FatWin32_.hpp"

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
            StarBase::InitMulti(gfx);
        }

        const auto& vertices = Star::Make(radius_, position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        const auto& indices = HollowBase::GenerateIndices(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_int_distribution<int> rgb_dist(0, 255);

        struct ConstantBuffer2
        {
            dx::XMFLOAT4 vertex_colors[6];
        };

        ConstantBuffer2 cb2 = {};

        for (std::size_t i = 0u; i < 6u; ++i)
        {
            cb2.vertex_colors[i] = dx::XMFLOAT4{
                static_cast<float>(rgb_dist(mrng)) / 255.0f,
                static_cast<float>(rgb_dist(mrng)) / 255.0f,
                static_cast<float>(rgb_dist(mrng)) / 255.0f,
                1.0f
            };
        }

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::PixelCBuffer<ConstantBuffer2>>(gfx, cb2));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}