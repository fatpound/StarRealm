module;

#include <FatNamespaces.hpp>

export module StarRealm.Entity.Star.Style.Fill:Hollow;

import <d3d11.h>;

import :Base;

import FatPound;

import std;

export namespace starrealm::entity::star_style::fill
{
    class Hollow final : public Base<Hollow>
    {
    public:
        explicit Hollow()                  = delete;
        explicit Hollow(const Hollow&)     = delete;
        explicit Hollow(Hollow&&) noexcept = delete;

        auto operator = (const Hollow&)     -> Hollow& = delete;
        auto operator = (Hollow&&) noexcept -> Hollow& = delete;
        ~Hollow() noexcept                             = delete;


    public:
        template <::std::integral T = ::std::uint32_t>
        static auto GenerateIndices(const ::std::size_t& vertex_count) -> ::std::vector<T>
        {
            ::std::vector<T> indices;

            indices.reserve(vertex_count + 1u);

            for (::std::size_t i{}; i < vertex_count; ++i)
            {
                indices.emplace_back(static_cast<T>(i));
            }

            indices.emplace_back(static_cast<T>(0u));

            return indices;
        }

        template <typename StarBase>
        static void InitStaticBinds()
        {
            StarBase::AddStaticBind_(::std::make_unique<FATSPACE_PIPELINE_ELEMENT::Topology>(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP));
        }


    protected:


    private:
    };
}
