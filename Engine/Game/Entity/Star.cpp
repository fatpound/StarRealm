module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module Star;

namespace dx = DirectX;

namespace fatpound::starrealm::entity
{
    Star::Star(const Descriptor& desc)
        :
        radius_(desc.radius),
        position_(desc.position),
        rotation_speed_(desc.rotation_speed),
        roll_(0.0f)
    {

    }

    auto Star::Make(const dx::XMFLOAT2& radius, const dx::XMFLOAT3& centre, std::size_t flare_count) -> std::vector<dx::XMFLOAT3>
    {
        std::vector<dx::XMFLOAT3> star;
        const std::size_t capacity = flare_count * 2u;

        star.reserve(capacity + 1u);

        const float dTheta = 2.0f * dx::XM_PI / static_cast<float>(capacity);

        for (std::size_t i = 0u; i < capacity; ++i)
        {
            const float rad = (i % 2u == 0u)
                ? radius.x
                : radius.y
                ;

            star.emplace_back(
                rad * std::cos(static_cast<float>(i) * dTheta) + centre.x,
                rad * std::sin(static_cast<float>(i) * dTheta) + centre.y,
                centre.z
            );
        }

        return star;
    }
    auto Star::MakeWithCentre(const dx::XMFLOAT2& radius, const dx::XMFLOAT3& centre, std::size_t flare_count) -> std::vector<dx::XMFLOAT3>
    {
        auto star = Star::Make(radius, centre, flare_count);
        
        star.emplace_back(centre.x, centre.y, centre.z);

        return star;
    }

    dx::XMMATRIX Star::GetTransformXM() const noexcept
    {
        const auto& pos_vec = dx::XMLoadFloat3(&position_);

        return dx::XMMatrixTranslationFromVector(dx::XMVectorNegate(pos_vec)) *
            dx::XMMatrixRotationZ(roll_) *
            dx::XMMatrixTranslationFromVector(pos_vec);
    }

    void Star::Update(float delta_time) noexcept
    {
        roll_ += (delta_time * rotation_speed_);
    }

    dx::XMFLOAT3 Star::GetPosition() const noexcept
    {
        return position_;
    }

    float Star::GetOuterRadius() const noexcept
    {
        return radius_.x;
    }
}