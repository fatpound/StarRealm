module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Fill:Filled;

export import :Base;

import <d3d11.h>;

import FatPound;

import std;

namespace dx = DirectX;

template <typename T>
concept MyVertex = std::same_as<T, ::dx::XMFLOAT3> or requires(T vertex)
{
    vertex.m_pos;
};

export namespace starrealm::entity::star_style::fill
{
    class Filled final : public Base<Filled>
    {
    public:
        explicit Filled()                  = delete;
        explicit Filled(const Filled&)     = delete;
        explicit Filled(Filled&&) noexcept = delete;

        auto operator = (const Filled&)     -> Filled& = delete;
        auto operator = (Filled&&) noexcept -> Filled& = delete;
        ~Filled() noexcept                             = delete;


    public:
        template
        <
            MyVertex V,
            bool WithCentre   = true,
            ::std::integral T = ::std::uint32_t
        >
        static auto GenerateIndices(const ::std::vector<V>& vertices) -> ::std::vector<T>
        {
            const auto vertex_count_no_centre = static_cast<T>(vertices.size() - 1u);

            ::std::vector<T> indices;

            indices.reserve(vertex_count_no_centre * 3u);

            for (T i = 1u; i <= vertex_count_no_centre - 1u; i += 2u)
            {
                for (T j{}; j < 2u; ++j)
                {
                    ::std::array<T, 3u> temp_idx{};

                    temp_idx[0u] = static_cast<T>(i % vertex_count_no_centre);
                    temp_idx[1u] = static_cast<T>(((j == 0) ? ((i + 1u) % vertex_count_no_centre) : (vertex_count_no_centre)));
                    temp_idx[2u] = static_cast<T>((i + 2u) % vertex_count_no_centre);

                    ReorderVertices_<>(vertices, temp_idx);

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
            if constexpr (std::same_as<V, ::dx::XMFLOAT3>)
            {
                return vertex.x;
            }
            else
            {
                return vertex.m_pos.x;
            }
        }

        template <MyVertex V>
        static float GetVertex_Y_(const V& vertex) noexcept
        {
            if constexpr (std::same_as<V, ::dx::XMFLOAT3>)
            {
                return vertex.y;
            }
            else
            {
                return vertex.m_pos.y;
            }
        }

        template <MyVertex V, ::std::integral T>
        static void ReorderVertices_(const ::std::vector<V>& vertices, ::std::array<T, 3u>& idx_arr)
        {
            ::std::ranges::sort(
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

            const auto& isClockwise = [](const V& v0, const V& v1, const V& v2) noexcept -> bool
            {
                return
                    (
                        (GetVertex_X_(v1) - GetVertex_X_(v0)) * (GetVertex_Y_(v2) - GetVertex_Y_(v0))
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
