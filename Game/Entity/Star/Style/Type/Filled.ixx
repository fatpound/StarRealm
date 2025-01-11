module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Type:Filled;

import :Base;

import FatPound;

import std;

template <typename T>
concept MyVertex = std::same_as<T, DirectX::XMFLOAT3> or requires(T vertex)
{
    vertex.pos;
};

export namespace starrealm::entity::star::style::type
{
    class Filled final : public Base_<Filled>
    {
    public:
        explicit Filled() = delete;
        explicit Filled(const Filled& src) = delete;
        explicit Filled(Filled&& src) = delete;

        auto operator = (const Filled& src) -> Filled& = delete;
        auto operator = (Filled&& src)      -> Filled& = delete;
        ~Filled() noexcept = delete;


    public:
        template
        <
            MyVertex V,
            bool WithCentre = true
        >
        static auto GenerateIndices(const std::vector<V>& vertices) -> std::vector<unsigned short int>
        {
            using idx_val_t = unsigned short int;

            const auto vertex_count_no_centre = static_cast<idx_val_t>(vertices.size() - 1u);

            std::vector<idx_val_t> indices;

            indices.reserve(vertex_count_no_centre * 3u);

            for (idx_val_t i = 1u; i <= vertex_count_no_centre - 1u; i += 2u)
            {
                for (idx_val_t j = 0u; j < 2u; ++j)
                {
                    std::array<idx_val_t, 3u> temp_idx{};

                    temp_idx[0u] = static_cast<idx_val_t>(i % vertex_count_no_centre);
                    temp_idx[1u] = static_cast<idx_val_t>(((j == 0) ? ((i + 1u) % vertex_count_no_centre) : (vertex_count_no_centre)));
                    temp_idx[2u] = static_cast<idx_val_t>((i + 2u) % vertex_count_no_centre);

                    ReorderVertices_(vertices, temp_idx);

                    indices.append_range(temp_idx);
                }
            }

            return indices;
        }

        template <typename StarBase>
        static void InitStaticBinds()
        {
            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
        }


    protected:


    private:
        template <MyVertex V>
        static float GetVertex_X_(const V& vertex) noexcept
        {
            if constexpr (std::is_same_v<V, ::DirectX::XMFLOAT3>)
            {
                return vertex.x;
            }
            else
            {
                return vertex.pos.x;
            }
        }

        template <MyVertex V>
        static float GetVertex_Y_(const V& vertex) noexcept
        {
            if constexpr (std::is_same_v<V, ::DirectX::XMFLOAT3>)
            {
                return vertex.y;
            }
            else
            {
                return vertex.pos.y;
            }
        }

        template <MyVertex V>
        static void ReorderVertices_(const std::vector<V>& vertices, std::array<unsigned short int, 3u>& idx_arr)
        {
            std::ranges::sort(
                idx_arr,
                [&](const auto& idx0, const auto& idx1) noexcept -> bool
                {
                    const auto y0 = GetVertex_Y_(vertices[idx0]);
                    const auto y1 = GetVertex_Y_(vertices[idx1]);

                    if (y0 not_eq y1)
                    {
                        return y0 < y1;
                    }

                    return GetVertex_X_(vertices[idx0]) < GetVertex_X_(vertices[idx1]);
                }
            );

            auto isClockwise = [](const V& v0, const V& v1, const V& v2) noexcept -> bool
            {
                return ((GetVertex_X_(v1) - GetVertex_X_(v0)) * (GetVertex_Y_(v2) - GetVertex_Y_(v0))
                        -
                        (GetVertex_Y_(v1) - GetVertex_Y_(v0)) * (GetVertex_X_(v2) - GetVertex_X_(v0))
                    )
                    < 0;
            };

            if (not isClockwise(vertices[idx_arr[0]], vertices[idx_arr[1]], vertices[idx_arr[2]]))
            {
                std::swap(idx_arr[1], idx_arr[2]);
            }
        };
    };
}