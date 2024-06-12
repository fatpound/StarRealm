module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.HollowSingle;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    HollowSingle::HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<HollowBase, SingleColorBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE::VertexShader>(gfx, L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::PixelShader>(gfx, L"PSColorSingle.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::InputLayout>(gfx, ied, pvsbc));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
        }

        const auto& vertices = Star::Make(radius_, position_, desc.flare_count);

        const auto& vertex_count = vertices.size();

        std::vector<unsigned short int> indices;
        indices.reserve(vertex_count + 1u);

        for (std::size_t i = 0u; i < vertex_count; ++i)
        {
            indices.emplace_back(static_cast<unsigned short int>(i));
        }

        indices.emplace_back(static_cast<unsigned short int>(0u));

        struct ConstantBuffer2
        {
            dx::XMFLOAT4 the_color;
        };

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_real_distribution<float> rgb_dist(0.0f, 1.0f);

        const ConstantBuffer2 cb2 =
        {
            dx::XMFLOAT4{
                rgb_dist(mrng),
                rgb_dist(mrng),
                rgb_dist(mrng),
                rgb_dist(mrng)
            }
        };

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::PixelCBuffer<ConstantBuffer2>>(gfx, cb2));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}