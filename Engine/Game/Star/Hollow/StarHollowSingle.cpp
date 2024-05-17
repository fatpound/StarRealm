module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#if _MSVC_LANG == 202002L
#if IN_DEBUG
#include <array>
#endif // IN_DEBUG
#endif // _MSVC_LANG == 202002L

module StarHollowSingle;

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
    StarHollowSingle::StarHollowSingle(Graphics& gfx, const Descriptor& desc)
        :
        StarBase<StarHollowSingle>(desc)
    {
        if (!StarBase::IsStaticInitialized_())
        {
            auto pvs = std::make_unique<VertexShader>(gfx, L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<PixelShader>(gfx, L"PSColorSingle.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            StarBase::AddStaticBind_(std::make_unique<InputLayout>(gfx, ied, pvsbc));
            StarBase::AddStaticBind_(std::make_unique<Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
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

        AddBind_(std::make_unique<PixelCBuffer<ConstantBuffer2>>(gfx, cb2));

        AddBind_(std::make_unique<VertexBuffer>(gfx, vertices));
        AddIndexBuffer_(std::make_unique<IndexBuffer>(gfx, indices));
        AddBind_(std::make_unique<TransformCBuffer>(gfx, *this));
    }
}