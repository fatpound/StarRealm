module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowMulti;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowMulti::HollowMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Hollow, style::effect::MultiColor>(gfx, desc)
    {
        using namespace style::type;
        using namespace style::effect;

        using StarBase = StarBase<Hollow, MultiColor>;

        if (not StarBase::IsStaticInitialized_())
        {
            Hollow::Init<StarBase>();
            MultiColor::Init<StarBase, false>(gfx);
        }

        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = Hollow::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));
        
        const auto& sbuf = MultiColor::ColorBase_::GeneratePixelSBuffer(desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelSBuffer<MultiColor::ColorBase_::SBuffer::Type>>(gfx, sbuf.vertex_colors));
    }
}