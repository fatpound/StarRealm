module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.FilledBase;

import FatPound.Win32.Direct3D11.Graphics;
import FatPound.Win32.Direct3D11.Pipeline;

import std;

template <class V>
concept MyVertex = requires(V vertex)
{
    requires
        requires { requires std::is_same_v<V, DirectX::XMFLOAT3>; }
        or
        requires { vertex.pos; };
};

export namespace fatpound::starrealm::entity::star
{
    class FilledBase final
    {
    public:
        template <MyVertex V>
        static auto GenerateIndices(const std::vector<V>& vertices) -> std::vector<unsigned short int>
        {
            const auto& vertex_count_no_centre = vertices.size() - 1u;

            std::vector<unsigned short int> indices;

            indices.reserve(vertex_count_no_centre * 3u);

            for (std::size_t i = 1u; i <= vertex_count_no_centre - 1u; i += 2u)
            {
                for (std::size_t j = 0u; j < 2u; ++j)
                {
                    std::array<std::size_t, 3u> temp_idx = {};

                    temp_idx[0u] = i % vertex_count_no_centre;
                    temp_idx[1u] = ((j == 0) ? ((i + 1u) % vertex_count_no_centre) : (vertex_count_no_centre));
                    temp_idx[2u] = (i + 2u) % vertex_count_no_centre;

                    FilledBase::ReorderTriangles_(vertices, temp_idx, indices);
                }
            }

            return indices;
        }

        template <class C>
        static void Init()
        {
            C::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }


    protected:


    private:
        template <MyVertex V>
        static float GetVertex_X_(const V& vertex)
        {
            if constexpr (std::is_same_v<V, DirectX::XMFLOAT3>)
            {
                return vertex.x;
            }
            else
            {
                return vertex.pos.x;
            }
        }

        template <MyVertex V>
        static float GetVertex_Y_(const V& vertex)
        {
            if constexpr (std::is_same_v<V, DirectX::XMFLOAT3>)
            {
                return vertex.y;
            }
            else
            {
                return vertex.pos.y;
            }
        }

        template <MyVertex V>
        static void ReorderTriangles_(const std::vector<V>& vertices, std::array<std::size_t, 3u>& idx_arr, std::vector<unsigned short int>& indices)
        {
            std::sort(
                idx_arr.begin(),
                idx_arr.end(),
                [&](const auto& idx0, const auto& idx1) -> bool
                {
                    return FilledBase::GetVertex_X_(vertices[idx0]) < FilledBase::GetVertex_X_(vertices[idx1]);
                }
            );

            if (FilledBase::GetVertex_Y_(vertices[idx_arr[1u]]) < FilledBase::GetVertex_Y_(vertices[idx_arr[2u]]))
            {
                std::swap(idx_arr[1u], idx_arr[2u]);
            }

            for (const std::size_t& idx : idx_arr)
            {
                indices.emplace_back(static_cast<unsigned short int>(idx));
            }
        };
    };
}