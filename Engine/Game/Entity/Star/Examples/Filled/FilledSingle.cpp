module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.FilledSingle;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    FilledSingle::FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<FilledBase, SingleColorBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE::VertexShader>(gfx, L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::PixelShader>(gfx, L"PSColorSingle.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "Color",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::InputLayout>(gfx, ied, pvsbc));
            StarBase::InitFilled();
        }

        const auto& vertices = Star::MakeWithCentre(radius_, position_, desc.flare_count);

        const auto& vertex_count_no_centre = vertices.size() - 1u;

        std::vector<unsigned short int> indices;
        indices.reserve(vertex_count_no_centre * 3u);

        const auto& sort_triangles = [&](std::array<std::size_t, 3u>& idx_arr) -> void
            {
                // TODO: remove sort if we can use only if's since the array size is 3
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