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
            StarBase::InitBlend(gfx);
            StarBase::InitFilled();
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

        for (const auto& vertex : Star::MakeWithCentre(radius_, position_, flare_count))
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
                        return vertices[idx0].pos.x < vertices[idx1].pos.x;
                    }
                );

                if (vertices[idx_arr[1u]].pos.y < vertices[idx_arr[2u]].pos.y)
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

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}