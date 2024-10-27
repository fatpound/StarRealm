module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Effect:Color.Multi;

export import :Base;

export import :Color.Base;

import FatPound;

import std;

export namespace starrealm::entity::star::style::effect
{
    class MultiColor final : public ColorBase_<MultiColor>
    {
    public:
        explicit MultiColor() = delete;
        explicit MultiColor(const MultiColor& src) = delete;
        explicit MultiColor(MultiColor&& src) = delete;

        auto operator = (const MultiColor& src) -> MultiColor& = delete;
        auto operator = (MultiColor&& src)      -> MultiColor& = delete;
        ~MultiColor() noexcept = delete;


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
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::PixelShader>(gfx.GetDevice(), L"PSColorMulti.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,                           0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD",  0, DXGI_FORMAT_R32_UINT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            if constexpr (ForFilled)
            {
                ied.insert(
                    ied.begin() + 1,
                    { "Color", 0, DXGI_FORMAT_B8G8R8A8_UNORM,  0,                          12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
            }

            StarBase::AddStaticBind_(std::make_unique<FATSPACE_PIPELINE_ELEMENT::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}