module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.FilledSingle;

import FatPound;

namespace dx = DirectX;

namespace starrealm::entity::star
{
    FilledSingle::FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<style::type::Filled, style::effect::SingleColor>(gfx, desc)
    {
        using namespace style::type;
        using namespace style::effect;

        if (not StarBase::IsStaticInitialized_())
        {
            Filled::Init<StarBase>();
            SingleColor::Init<StarBase>(gfx);
        }

        const auto& vertices = Star::Make<true>(m_radiuses_, m_position_, desc.flare_count);
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::VertexBuffer>(gfx, vertices));

        const auto& indices = Filled::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE_ELEMENT::IndexBuffer>(gfx, indices));

        const auto& cbuf = SingleColor::ColorBase_::GeneratePixelCBuffer();
        AddBind_(std::make_unique<NAMESPACE_PIPELINE_RESOURCE::PixelCBuffer<SingleColor::ColorBase_::CBuffer>>(gfx, cbuf));
    }
}