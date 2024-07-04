module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Type.HollowBase;

import FatPound.Win32.Direct3D11.Graphics;
import FatPound.Win32.Direct3D11.Pipeline;

import std;

export namespace fatpound::starrealm::entity::star
{
    class HollowBase final
    {
    public:
        template <class Base>
        static void Init()
        {
            Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
        }

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


    protected:


    private:
    };
}