module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.FilledBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    class FilledBase final
    {
    public:
        template <class V>
        requires requires(V vertex)
        {
            requires requires { vertex.pos; } or requires{ requires std::is_same_v<V, DirectX::XMFLOAT3>; };
        }
        static void ReorderTriangles(const std::vector<V>& vertices, std::array<std::size_t, 3u>& idx_arr, std::vector<unsigned short int>& indices)
        {
            if constexpr (std::is_same_v<V, DirectX::XMFLOAT3>)
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
            }
            else
            {
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
            }

            for (const std::size_t& idx : idx_arr)
            {
                indices.emplace_back(static_cast<unsigned short int>(idx));
            }
        };


    protected:


    private:
    };
}