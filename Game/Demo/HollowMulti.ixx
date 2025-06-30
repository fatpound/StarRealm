module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.HollowMulti;

import <d3d11.h>;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::demo
{
    class HollowMulti final : public entity::StarBase<STARREALM_ENTITY_FILL::Hollow, STARREALM_ENTITY_COLOR::Multi>
    {
    public:
        explicit HollowMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
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

            AddBind_(std::make_unique<FATSPACE_D3D11::pipeline::VertexBuffer>(gfx.GetDevice(), vbd, vertices));

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
                std::make_unique<FATSPACE_D3D11::pipeline::IndexBuffer>(
                    gfx.GetDevice(),
                    ibd,
                    DXGI_FORMAT_R32_UINT,
                    indices
                )
            );

            const auto vxcolors = STARREALM_ENTITY_COLOR::Multi::ColoringBase::GeneratePixelSBuffer(desc.flare_count).vertex_colors;

            const D3D11_BUFFER_DESC sbd
            {
                .ByteWidth           = static_cast<UINT>(vxcolors.size() * sizeof(decltype(vxcolors)::value_type)),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_SHADER_RESOURCE,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED,
                .StructureByteStride = sizeof(decltype(vxcolors)::value_type)
            };

            const D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc
            {
                .Format        = DXGI_FORMAT_UNKNOWN,
                .ViewDimension = D3D11_SRV_DIMENSION_BUFFER,
                .Buffer        =
#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-designated-field-initializers"
#endif
                               {
                                   .ElementWidth = static_cast<UINT>(vxcolors.size())
                               }
#ifdef __clang__
    #pragma clang diagnostic pop
#endif
            };

            AddBind_(
                std::make_unique<FATSPACE_D3D11::pipeline::PixelSBuffer<STARREALM_ENTITY_COLOR::Multi::ColoringBase::SBuffer::Type>>(
                    gfx.GetDevice(),
                    gfx.GetImmediateContext(),
                    sbd,
                    srvDesc,
                    vxcolors
                )
            );
        }

        explicit HollowMulti()                       = delete;
        explicit HollowMulti(const HollowMulti&)     = delete;
        explicit HollowMulti(HollowMulti&&) noexcept = delete;

        auto operator = (const HollowMulti&)     -> HollowMulti& = delete;
        auto operator = (HollowMulti&&) noexcept -> HollowMulti& = delete;
        virtual ~HollowMulti() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
