module;

#include <FatNamespaces.hxx>

export module StarRealm.Entity.Star.Style.Color:Multi;

import <d3d11.h>;
import <DirectXMath.h>;

import :Base;
import :ColoringBase;

import FatPound;

import std;

export namespace starrealm::entity::star_style::color
{
    class Multi final : public ColoringBase<Multi>
    {
    public:
        explicit Multi()                 = delete;
        explicit Multi(const Multi&)     = delete;
        explicit Multi(Multi&&) noexcept = delete;

        auto operator = (const Multi&)     -> Multi& = delete;
        auto operator = (Multi&&) noexcept -> Multi& = delete;
        ~Multi() noexcept                            = delete;


    public:
        template
        <
            typename StarBase,
            bool ForFilled = true
        >
        static void InitStaticBinds(FATSPACE_D3D11::Graphics<>& gfx)
        {
            auto pvs = std::make_unique<FATSPACE_PIPELINE_ELEMENT::VertexShader>(gfx.GetDevice(), L"VSColorMulti.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move<>(pvs));
            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::PixelShader>(gfx.GetDevice(), L"PSColorMulti.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0U, DXGI_FORMAT_R32G32B32_FLOAT, 0U,                           0U, D3D11_INPUT_PER_VERTEX_DATA, 0U },
                { "TEXCOORD",  0U, DXGI_FORMAT_R32_UINT,        0U, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0U }
            };

            if constexpr (ForFilled)
            {
                ied.insert(
                    ied.begin() + 1U,
                    { "Color", 0U, DXGI_FORMAT_B8G8R8A8_UNORM,  0U,                          12U, D3D11_INPUT_PER_VERTEX_DATA, 0U }
                );
            }

            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}
