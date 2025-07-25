module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowSingle;

import <d3d11.h>;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::demo
{
    class HollowSingle final : public entity::StarBase<STARREALM_ENTITY_FILL::Hollow, STARREALM_ENTITY_COLOR::Single>
    {
    public:
        explicit HollowSingle(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto vertices = Star::Make<>(m_radiuses_, m_position_, desc.flare_count);

            const D3D11_BUFFER_DESC vbd
            {
                .ByteWidth           = static_cast<UINT>(vertices.size() * sizeof(decltype(vertices)::value_type)),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_VERTEX_BUFFER,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = 0U,
                .StructureByteStride = sizeof(decltype(vertices)::value_type)
            };

            AddBind_(std::make_unique<FATSPACE_D3D11::resource::VertexBuffer>(gfx.GetDevice(), vbd, vertices));



            const auto indices = STARREALM_ENTITY_FILL::Hollow::GenerateIndices<>(vertices.size());

            const D3D11_BUFFER_DESC ibd
            {
                .ByteWidth           = static_cast<UINT>(indices.size() * sizeof(decltype(indices)::value_type)),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_INDEX_BUFFER,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = 0U,
                .StructureByteStride = sizeof(decltype(indices)::value_type)
            };

            AddIndexBuffer_(
                std::make_unique<FATSPACE_D3D11::resource::IndexBuffer>(
                    gfx.GetDevice(),
                    ibd,
                    DXGI_FORMAT_R32_UINT,
                    indices
                )
            );



            const auto pixcbuf = STARREALM_ENTITY_COLOR::Single::ColoringBase::GeneratePixelCBuffer();

            const D3D11_BUFFER_DESC cbd
            {
                .ByteWidth           = sizeof(pixcbuf),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0U,
                .StructureByteStride = 0U
            };

            AddBind_(
                std::make_unique<FATSPACE_D3D11::resource::PixelCBuffer<STARREALM_ENTITY_COLOR::Single::ColoringBase::CBuffer>>(
                    gfx.GetDevice(),
                    cbd,
                    pixcbuf
                )
            );
        }

        explicit HollowSingle()                        = delete;
        explicit HollowSingle(const HollowSingle&)     = delete;
        explicit HollowSingle(HollowSingle&&) noexcept = delete;

        auto operator = (const HollowSingle&)     -> HollowSingle& = delete;
        auto operator = (HollowSingle&&) noexcept -> HollowSingle& = delete;
        virtual ~HollowSingle() noexcept override final            = default;


    protected:


    private:
    };
}

module : private;
