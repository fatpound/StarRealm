module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Effect.SingleColorBase;

import StarRealm.Entity.Star.Style.Effect.ColorBase;

import FatPound.Win32.D3D11.Graphics;
import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::starrealm::entity::star
{
    class SingleColorBase final : public ColorBase
    {
    public:
        template <
            class Base,
            bool ForFilled = true
        >
        static void Init(NAMESPACE_D3D11::Graphics& gfx)
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE::VertexShader>(gfx, L"VSColorSingle.cso");
            auto pvsbc = pvs->GetBytecode();
            Base::AddStaticBind_(std::move(pvs));
            Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::PixelShader>(gfx, L"PSColorSingle.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            if constexpr (ForFilled)
            {
                ied.push_back(
                    { "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM,  0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
            }

            Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE::InputLayout>(gfx, ied, pvsbc));
        }


    protected:


    private:
    };
}