module;

#include <FatNamespaces.hxx>

export module StarRealm.Entity.Star.Style.Color:Single;

import <d3d11.h>;
import <DirectXMath.h>;

import :Base;
import :ColoringBase;

import FatPound;

import std;

export namespace starrealm::entity::star_style::color
{
    class Single final : public ColoringBase<Single>
    {
    public:
        explicit Single()                  = delete;
        explicit Single(const Single&)     = delete;
        explicit Single(Single&&) noexcept = delete;

        auto operator = (const Single&)     -> Single& = delete;
        auto operator = (Single&&) noexcept -> Single& = delete;
        ~Single() noexcept                             = delete;


    public:
        template
        <
            typename StarBase,
            bool ForFilled = true
        >
        static void InitStaticBinds(fatpound::win32::d3d11::Graphics<>& gfx)
        {
            auto pvs = std::make_unique<fatpound::win32::d3d11::pipeline::VertexShader>(gfx.GetDevice(), L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            StarBase::AddStaticBind_(std::move<>(pvs));
            StarBase::AddStaticBind_(std::make_unique<fatpound::win32::d3d11::pipeline::PixelShader>(gfx.GetDevice(), L"PSColorSingle.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0U, DXGI_FORMAT_R32G32B32_FLOAT, 0U,  0U, D3D11_INPUT_PER_VERTEX_DATA, 0U }
            };

            if constexpr (ForFilled)
            {
                ied.push_back(
                    { "Color", 0U, DXGI_FORMAT_B8G8R8A8_UNORM,  0U, 12U, D3D11_INPUT_PER_VERTEX_DATA, 0U }
                );
            }

            StarBase::AddStaticBind_(std::make_unique<fatpound::win32::d3d11::pipeline::InputLayout>(gfx.GetDevice(), ied, pvsbc));
        }


    protected:


    private:
    };
}
