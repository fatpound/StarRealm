module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Effect:Blend;

import :Base;

import StarRealm.Entity.Star;

import FatPound;

import std;

export namespace starrealm::entity::star::style::effect
{
    class Blend final : public EffectBase_<Blend>
    {
    public:
        explicit Blend() = delete;
        explicit Blend(const Blend& src) = delete;
        explicit Blend(Blend&& src) = delete;

        Blend& operator = (const Blend& src) = delete;
        Blend& operator = (Blend&& src) = delete;
        ~Blend() noexcept = delete;


    public:
        struct Vertex final
        {
            ::DirectX::XMFLOAT3 pos;

            NAMESPACE_UTIL::Color color;
        };


    public:
        template <bool With_Centre = true>
        static auto GenerateVertices(Star::RadiusPack radiuses, DirectX::XMFLOAT3 position, std::size_t flare_count)
        {
            std::vector<Blend::Vertex> vertices;

            vertices.reserve(flare_count * 2u + 1u);

            std::minstd_rand mrng(std::random_device{}());
            std::uniform_int_distribution<int> rgb_dist(0, 255);

            std::vector<DirectX::XMFLOAT3> star_vertices;

            star_vertices = Star::Make<With_Centre>(radiuses, position, flare_count);

            for (const auto& vertex : star_vertices)
            {
                vertices.emplace_back(
                    vertex,
                    NAMESPACE_UTIL::Color(
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        static_cast<unsigned char>(rgb_dist(mrng)),
                        255
                    )
                );
            }

            return vertices;
        }

        template <class Star_Base>
        static void Init(NAMESPACE_D3D11::Graphics& gfx)
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(gfx, L"VSColorBlend.cso");
            auto pvsbc = pvs->GetBytecode();
            Star_Base::AddStaticBind_(std::move(pvs));
            Star_Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::PixelShader>(gfx, L"PSColorBlend.cso"));

            const std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "Color",    0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            Star_Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::InputLayout>(gfx, ied, pvsbc));
        }


    protected:


    private:
    };
}