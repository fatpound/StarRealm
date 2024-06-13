module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.FilledBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    template <class V>
    concept MyVertex = requires(V vertex)
    {
        requires requires { vertex.pos; } or requires{ requires std::is_same_v<V, DirectX::XMFLOAT3>; };
    };

    class FilledBase final
    {
    public:
        template <MyVertex V>
        static void ReorderTriangles(const std::vector<V>& vertices, std::array<std::size_t, 3u>& idx_arr, std::vector<unsigned short int>& indices)
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
    };
}