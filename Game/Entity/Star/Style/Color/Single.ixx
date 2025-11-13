module;

#include <_macros/Namespaces.hxx>

export module StarRealm.Entity.Star.Style.Color:Single;

import <d3d11_4.h>;
import <d3dcompiler.h>;
import <wrl.h>;

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
        static void InitStaticBinds(FATSPACE_D3D11::Graphics<>& gfx)
        {
            {
                Microsoft::WRL::ComPtr<ID3DBlob> pVSBlob;

                if (FAILED(::D3DReadFileToBlob(L"VSColorSingle.cso", &pVSBlob)))
                {
                    throw std::runtime_error("CANNOT read Vertex Shader to D3D Blob!");
                }

                StarBase::AddStaticBind_(std::make_unique<FATSPACE_D3D11::shader::VertexShader>(gfx.GetDevice(), pVSBlob));

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

                StarBase::AddStaticBind_(std::make_unique<FATSPACE_D3D11::core::InputLayout>(gfx.GetDevice(), ied, pVSBlob));
            }

            StarBase::AddStaticBind_(std::make_unique<FATSPACE_D3D11::shader::PixelShader>(gfx.GetDevice(), std::wstring(L"PSColorSingle.cso")));
        }


    protected:


    private:
    };
}
