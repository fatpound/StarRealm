module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Type.HollowBase;

import StarRealm.Entity.Star.Style.TypeBase;

import FatPound;

import std;

export namespace starrealm::entity::star
{
    class HollowBase final : public StyleType<HollowBase>
    {
    public:
        template <typename T>
        static auto GenerateIndices(std::size_t vertex_count) -> std::vector<T>
        {
            std::vector<T> indices;

            indices.reserve(vertex_count + 1u);

            for (std::size_t i = 0u; i < vertex_count; ++i)
            {
                indices.emplace_back(static_cast<T>(i));
            }

            indices.emplace_back(static_cast<T>(0u));

            return indices;
        }

        template <class Star_Base>
        static void Init()
        {
            Star_Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
        }


    protected:


    private:
    };
}