module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarFilledMulti;

import FatColor;
import VertexBuffer;
import VertexShader;
import PixelShader;
import InputLayout;
import Topology;
import PixelCBuffer;
import TransformCBuffer;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    StarFilledMulti::StarFilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<StarFilledMulti>(desc)
    {
        if (!StarBase::IsStaticInitialized_())
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE::VertexShader>(gfx, L"VSColorIndexed.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::PixelShader>(gfx, L"PSColorIndexed.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::InputLayout>(gfx, ied, pvsbc));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }

        // The non-Blend effect Vertex is the same as Star::Make's dx::XMFLOAT3
        const auto& vertices = Star::MakeWithCentre(radius_, position_, desc.flare_count);

        const auto& vertex_count_no_centre = vertices.size() - 1u;

        std::vector<unsigned short int> indices;
        indices.reserve(vertex_count_no_centre * 3u);

        const auto& sort_triangles = [&](std::array<std::size_t, 3u>& idx_arr) -> void
            {
                std::sort(
                    idx_arr.begin(),
                    idx_arr.end(),
                    [&](const auto& idx0, const auto& idx1) -> bool
                    {
                        return vertices[idx0].x < vertices[idx1].x;
                    }
                );

                if (vertices[idx_arr[1u]].y < vertices[idx_arr[2u]].y)
                {
                    std::swap(idx_arr[1u], idx_arr[2u]);
                }

                for (const std::size_t& idx : idx_arr)
                {
                    indices.emplace_back(static_cast<unsigned short int>(idx));
                }
            };

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        for (std::size_t i = 1u; i <= vertex_count_no_centre - 1u; i += 2u)
        {
            for (std::size_t j = 0u; j < 2u; ++j)
            {
                std::array<std::size_t, 3u> temp_idx;

                temp_idx[0u] = i % vertex_count_no_centre;
                temp_idx[1u] = ((j == 0) ? ((i + 1u) % vertex_count_no_centre) : (vertex_count_no_centre));
                temp_idx[2u] = (i + 2u) % vertex_count_no_centre;

                sort_triangles(temp_idx);
            }
        }

        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        struct ConstantBuffer2
        {
            dx::XMFLOAT4 vertex_colors[6];
        };

        ConstantBuffer2 cb2 = {};

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_int_distribution<int> rgb_dist(0, 255);

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