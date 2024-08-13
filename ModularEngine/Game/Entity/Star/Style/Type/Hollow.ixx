module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Type.Hollow;

import StarRealm.Entity.Star.Style.TypeBase;

import FatPound;

import std;

export namespace starrealm::entity::star::style::type
{
    class Hollow final : public TypeBase_<Hollow>
    {
    public:
        explicit Hollow() = delete;
        explicit Hollow(const Hollow& src) = delete;
        explicit Hollow(Hollow&& src) = delete;

        Hollow& operator = (const Hollow& src) = delete;
        Hollow& operator = (Hollow&& src) = delete;
        ~Hollow() noexcept = delete;


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