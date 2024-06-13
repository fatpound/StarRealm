module;

#include "../../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <d3d11.h>

module StarRealm.Entity.Star.FilledBlend;

import FatPound.Win32;
import FatPound.Util;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    FilledBlend::FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc)
        :
        StarBase<FilledBase, BlendBase>(desc)
    {
        if (not StarBase::IsStaticInitialized_())
        {
            StarBase::InitFilled();
            StarBase::InitBlend(gfx);
        }

        std::minstd_rand mrng(std::random_device{}());
        std::uniform_int_distribution<int> rgb_dist(0, 255);

        const auto& flare_count = desc.flare_count;

        std::vector<BlendBase::Vertex> vertices;
        vertices.reserve(flare_count * 2u + 1u);

        for (const auto& vertex : Star::MakeWithCentre(radius_, position_, flare_count))
        {
            vertices.emplace_back(
                vertex,
                fatpound::util::Color(
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    static_cast<unsigned char>(rgb_dist(mrng)),
                    255
                )
            );
        }
        AddBind_(std::make_unique<NAMESPACE_PIPELINE::VertexBuffer>(gfx, vertices));

        const auto& indices = FilledBase::GenerateIndices(vertices);
        AddIndexBuffer_(std::make_unique<NAMESPACE_PIPELINE::IndexBuffer>(gfx, indices));

        AddBind_(std::make_unique<NAMESPACE_PIPELINE::TransformCBuffer>(gfx, *this));
    }
}