module;

#include <_macros/Namespaces.hxx>

#include <StarRealmNamespaces.hpp>

export module StarRealm.Demo.FilledSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::demo
{
    class FilledSingle final : public entity::StarBase<STARREALM_ENTITY_FILL::Filled, STARREALM_ENTITY_COLOR::Single>
    {
    public:
        explicit FilledSingle(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTILITY::ViewXM& worldView)
            :
            StarBase(gfx, desc, worldView)
        {
            const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);

            AddBind_(std::make_unique<FATSPACE_D3D11::pipeline::VertexBuffer>(gfx.GetDevice(), vertices));

            AddIndexBuffer_(
                std::make_unique<FATSPACE_D3D11::pipeline::IndexBuffer>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_FILL::Filled::GenerateIndices<>(vertices)
                )
            );

            AddBind_(
                std::make_unique<FATSPACE_D3D11::pipeline::PixelCBuffer<STARREALM_ENTITY_COLOR::Single::ColoringBase::CBuffer>>(
                    gfx.GetDevice(),
                    STARREALM_ENTITY_COLOR::Single::ColoringBase::GeneratePixelCBuffer()
                )
            );
        }

        explicit FilledSingle()                        = delete;
        explicit FilledSingle(const FilledSingle&)     = delete;
        explicit FilledSingle(FilledSingle&&) noexcept = delete;

        auto operator = (const FilledSingle&)     -> FilledSingle& = delete;
        auto operator = (FilledSingle&&) noexcept -> FilledSingle& = delete;
        virtual ~FilledSingle() noexcept override final            = default;


    protected:


    private:
    };
}

module : private;
