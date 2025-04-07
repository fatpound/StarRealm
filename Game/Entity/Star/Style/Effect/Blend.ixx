module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Effect:Blend;

export import :Base;

import <d3d11.h>;

import StarRealm.Entity.Star;

import FatPound;

import std;

export namespace starrealm::entity::star::style::effect
{
    class Blend final : public Base_<Blend>
    {
    public:
        struct Vertex final
        {
            ::DirectX::XMFLOAT3 pos;

            FATSPACE_UTIL::Color color;
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
                const Star::RadiusPack radiuses,
                const ::DirectX::XMFLOAT3 position,
                const std::size_t flare_count
            )
        {
            std::vector<Blend::Vertex> vertices;

            vertices.reserve(flare_count * 2u + 1u);

            std::minstd_rand mrng(std::random_device{}());
            std::uniform_int_distribution<int> rgb_dist(0, 255);

            std::vector<::DirectX::XMFLOAT3> star_vertices;

            star_vertices = Star::Make<WithCentre>(radiuses, position, flare_count);

            for (const auto& vertex : star_vertices)
            {
                vertices.emplace_back(
                    vertex,
                    FATSPACE_UTIL::Color(
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        255
                    )
                );
            }

            return vertices;
        }

        template <typename StarBase>
        static void InitStaticBinds(FATSPACE_D3D11::Graphics<>& gfx)
        {
            auto pvs = std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexShader>(gfx.GetDevice(), L"VSColorBlend.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::PixelShader>(gfx.GetDevice(), L"PSColorBlend.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "Color",    0, DXGI_FORMAT_B8G8R8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}
