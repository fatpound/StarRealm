module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Effect:Color.Single;

export import :Base;

export import :Color.Base;

import FatPound;

import std;

export namespace starrealm::entity::star::style::effect
{
    class SingleColor final : public ColorBase_<SingleColor>
    {
    public:
        explicit SingleColor() = delete;
        explicit SingleColor(const SingleColor& src) = delete;
        explicit SingleColor(SingleColor&& src) = delete;

        auto operator = (const SingleColor& src) -> SingleColor& = delete;
        auto operator = (SingleColor&& src)      -> SingleColor& = delete;
        ~SingleColor() noexcept = delete;


    public:
        template
        <
            typename StarBase,
            bool ForFilled = true
        >
        static void InitStaticBinds(NAMESPACE_D3D11::Graphics<>& gfx)
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(gfx.GetDevice(), L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move(pvs));
            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::PixelShader>(gfx.GetDevice(), L"PSColorSingle.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            if constexpr (ForFilled)
            {
                ied.push_back(
                    { "Color", 0, DXGI_FORMAT_B8G8R8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
            }

            StarBase::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}