module;

#include "../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

#if _MSVC_LANG == 202002L
#ifndef NDEBUG
#include <array>
#endif // !NDEBUG
#endif // _MSVC_LANG == 202002L

module StarHollowBlend;

import FatColor;
import VertexBuffer;
import VertexShader;
import PixelShader;
import InputLayout;
import Topology;
import TransformCBuffer;

namespace dx = DirectX;

using namespace fatpound::win32::d3d11;

namespace fatpound::starrealm
{
    StarHollowBlend::StarHollowBlend(Graphics& gfx, const Descriptor& desc)
        :
        StarBase<StarHollowBlend>(desc)
    {
        if (!IsStaticInitialized_())
        {
            auto pvs = std::make_unique<VertexShader>(gfx, L"VSColorBlend.cso");
            auto pvsbc = pvs->GetBytecode();
            AddStaticBind_(std::move(pvs));
            AddStaticBind_(std::make_unique<PixelShader>(gfx, L"PSColorBlend.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "Color",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            AddStaticBind_(std::make_unique<InputLayout>(gfx, ied, pvsbc));
            AddStaticBind_(std::make_unique<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
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

        for (const auto& vertex : Star::Make(radius_.x, radius_.y, position_, flare_count, false))
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

        AddBind_(std::make_unique<VertexBuffer>(gfx, vertices));
        AddIndexBuffer_(std::make_unique<IndexBuffer>(gfx, indices));
        AddBind_(std::make_unique<TransformCBuffer>(gfx, *this));
    }
}