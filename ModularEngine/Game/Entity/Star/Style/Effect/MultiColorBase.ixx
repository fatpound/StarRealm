module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module StarRealm.Entity.Star.Style.Effect.MultiColorBase;

import StarRealm.Entity.Star.Style.Effect.ColorBase;

import FatPound;

import std;

export namespace starrealm::entity::star
{
    class MultiColorBase final : public ColorBase<MultiColorBase>
    {
    public:
        explicit MultiColorBase() = delete;
        explicit MultiColorBase(const MultiColorBase& src) = delete;
        explicit MultiColorBase(MultiColorBase&& src) = delete;

        MultiColorBase& operator = (const MultiColorBase& src) = delete;
        MultiColorBase& operator = (MultiColorBase&& src) = delete;
        ~MultiColorBase() noexcept = delete;


    public:
        template <
            class Star_Base,
            bool For_Filled = true
        >
        static void Init(NAMESPACE_D3D11::Graphics& gfx)
        {
            auto pvs = std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexShader>(gfx, L"VSColorMulti.cso");
            auto pvsbc = pvs->GetBytecode();
            Star_Base::AddStaticBind_(std::move(pvs));
            Star_Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::PixelShader>(gfx, L"PSColorMulti.cso"));

            std::vector<D3D11_INPUT_ELEMENT_DESC> ied =
            {
                { "Position",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0,                           0u, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                { "TEXCOORD",  0, DXGI_FORMAT_R32_UINT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
            };

            if constexpr (For_Filled)
            {
                ied.insert(
                    ied.begin() + 1,
                    { "Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM,  0,                          12u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
                );
            }

            Star_Base::AddStaticBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::InputLayout>(gfx, ied, pvsbc));
        }


    protected:


    private:
    };
}