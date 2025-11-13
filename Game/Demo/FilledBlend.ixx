module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.FilledBlend;

import <d3d11_4.h>;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

import std;

export namespace starrealm::demo
{
    class FilledBlend final : public entity::StarBase<STARREALM_ENTITY_FILL::Filled, STARREALM_ENTITY_COLOR::Blend>
    {
    public:
        explicit FilledBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto vertices = STARREALM_ENTITY_COLOR::Blend::GenerateVertices<>(m_radiuses_, m_position_, desc.flare_count);

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

            const auto indices = STARREALM_ENTITY_FILL::Filled::GenerateIndices<>(vertices);

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
        }

        explicit FilledBlend()                       = delete;
        explicit FilledBlend(const FilledBlend&)     = delete;
        explicit FilledBlend(FilledBlend&&) noexcept = delete;

        auto operator = (const FilledBlend&)     -> FilledBlend& = delete;
        auto operator = (FilledBlend&&) noexcept -> FilledBlend& = delete;
        virtual ~FilledBlend() noexcept override final           = default;


    protected:


    private:
    };
}

module : private;
