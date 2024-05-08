module;

#include "../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

#if _MSVC_LANG == 202002L
#ifndef NDEBUG
#include <array>
#endif // !NDEBUG
#endif // _MSVC_LANG == 202002L

module StarHollowMulti;

import FatColor;
import VertexBuffer;
import VertexShader;
import PixelShader;
import InputLayout;
import Topology;
import PixelCBuffer;
import TransformCBuffer;

namespace dx = DirectX;

using namespace fatpound::win32::d3d11;

namespace fatpound::starrealm
{
    StarHollowMulti::StarHollowMulti(Graphics& gfx, const Descriptor& desc)
        :
        StarBase<StarHollowMulti>(desc)
    {
        if (!IsStaticInitialized_())
        {
            auto pvs = std::make_unique<VertexShader>(gfx, L"VSColorIndexed.cso");
            auto pvsbc = pvs->GetBytecode();
            AddStaticBind_(std::move(pvs));
            AddStaticBind_(std::make_unique<PixelShader>(gfx, L"PSColorIndexed.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            AddStaticBind_(std::make_unique<InputLayout>(gfx, ied, pvsbc));
            AddStaticBind_(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
        }

        const auto& vertices = Star::Make(radius_.x, radius_.y, position_, desc.flare_count, false);
        const auto& vertex_count = vertices.size();
        AddBind_(std::make_unique<VertexBuffer>(gfx, vertices));

        std::vector<unsigned short int> indices;
        indices.reserve(vertex_count + 1u);

        for (std::size_t i = 0u; i < vertex_count; ++i)
        {
            indices.emplace_back(static_cast<unsigned short int>(i));
        }

        indices.emplace_back(static_cast<unsigned short int>(0u));

        AddIndexBuffer_(std::make_unique<IndexBuffer>(gfx, indices));

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

        AddBind_(std::make_unique<PixelCBuffer<ConstantBuffer2>>(gfx, cb2));

        AddBind_(std::make_unique<TransformCBuffer>(gfx, *this));
    }
}