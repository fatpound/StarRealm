module;

#include <FatNamespaces.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Color:Blend;

import <d3d11.h>;

import :Base;

import StarRealm.Entity.Star;

import FatPound;

import std;

namespace dx = DirectX;

export namespace starrealm::entity::star_style::color
{
    class Blend final : public Base<Blend>
    {
    public:
        struct Vertex final
        {
            ::dx::XMFLOAT3 m_pos;

            FATSPACE_UTIL::Color m_color;
        };


    public:
        explicit Blend()                 = delete;
        explicit Blend(const Blend&)     = delete;
        explicit Blend(Blend&&) noexcept = delete;

        auto operator = (const Blend&)     -> Blend& = delete;
        auto operator = (Blend&&) noexcept -> Blend& = delete;
        ~Blend() noexcept                            = delete;


    public:
        template <bool WithCentre = true>
        static auto GenerateVertices(
            const Star::RadiusPack& radiuses,
            const ::dx::XMFLOAT3& position,
            const ::std::size_t& flare_count)
        {
            ::std::vector<Blend::Vertex> vertices;
            vertices.reserve(flare_count * 2U + 1U);

            for (const auto& vertex : Star::Make<WithCentre>(radiuses, position, flare_count))
            {
                vertices.emplace_back(
                    vertex,
                    FATSPACE_UTIL::Color(
                        FATSPACE_RANDOM::RandUInt<unsigned char>(),
                        FATSPACE_RANDOM::RandUInt<unsigned char>(),
                        FATSPACE_RANDOM::RandUInt<unsigned char>(),
                        255U
                    )
                );
            }

            return vertices;
        }

        template <typename StarBase>
        static void InitStaticBinds(FATSPACE_D3D11::Graphics<>& gfx)
        {
            auto pvs = ::std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexShader>(gfx.GetDevice(), L"VSColorBlend.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(::std::move<>(pvs));
            StarBase::AddStaticBind_(::std::make_unique<FATSPACE_PIPELINE_ELEMENT::PixelShader>(gfx.GetDevice(), L"PSColorBlend.cso"));

            const ::std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0U, DXGI_FORMAT_R32G32B32_FLOAT, 0U,  0U, D3D11_INPUT_PER_VERTEX_DATA, 0U },
                { "Color",    0U, DXGI_FORMAT_B8G8R8A8_UNORM,  0U, 12U, D3D11_INPUT_PER_VERTEX_DATA, 0U }
            };

            StarBase::AddStaticBind_(::std::make_unique<FATSPACE_PIPELINE_ELEMENT::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}
