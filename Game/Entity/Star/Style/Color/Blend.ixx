module;

#include <_macros/Namespaces.hxx>

export module StarRealm.Entity.Star.Style.Color:Blend;

import <d3d11.h>;
import <DirectXMath.h>;

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
            dx::XMFLOAT3 m_pos;

            FATSPACE_UTILITY::Color m_color;
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
            const dx::XMFLOAT3& position,
            const std::size_t& flare_count)
        {
            std::vector<Blend::Vertex> vertices;
            vertices.reserve(flare_count * 2U + 1U);

            std::minstd_rand rng(std::random_device{}());
            std::uniform_int_distribution<std::uint32_t> dist;

            for (const auto& vertex : Star::Make<WithCentre>(radiuses, position, flare_count))
            {
                vertices.emplace_back(vertex, FATSPACE_RANDOM::RandColor<>(rng, dist));
            }

            return vertices;
        }

        template <typename StarBase>
        static void InitStaticBinds(fatpound::win32::d3d11::Graphics<>& gfx)
        {
            auto pvs = std::make_unique<fatpound::win32::d3d11::pipeline::VertexShader>(gfx.GetDevice(), L"VSColorBlend.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move<>(pvs));
            StarBase::AddStaticBind_(std::make_unique<fatpound::win32::d3d11::pipeline::PixelShader>(gfx.GetDevice(), L"PSColorBlend.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0U, DXGI_FORMAT_R32G32B32_FLOAT, 0U,  0U, D3D11_INPUT_PER_VERTEX_DATA, 0U },
                { "Color",    0U, DXGI_FORMAT_B8G8R8A8_UNORM,  0U, 12U, D3D11_INPUT_PER_VERTEX_DATA, 0U }
            };

            StarBase::AddStaticBind_(std::make_unique<fatpound::win32::d3d11::pipeline::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}
