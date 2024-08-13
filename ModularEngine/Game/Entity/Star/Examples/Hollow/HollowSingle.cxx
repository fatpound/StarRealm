module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.HollowSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    HollowSingle::HollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Hollow, style::effect::SingleColor>(gfx, desc)
    {
        using namespace style::type;
        using namespace style::effect;

        if (not StarBase::IsStaticInitialized_())
        {
            Hollow::Init<StarBase>();
            SingleColor::Init<StarBase, false>(gfx);
        }

        const auto& vertices = Star::Make(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = Hollow::GenerateIndices<unsigned short int>(vertices.size());
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& cbuf = SingleColor::ColorBase_::GeneratePixelCBuffer();
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelCBuffer<SingleColor::ColorBase_::CBuffer>>(gfx, cbuf));
    }
}