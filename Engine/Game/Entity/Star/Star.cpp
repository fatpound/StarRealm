module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module StarRealm.Entity.Star;

namespace dx = DirectX;

namespace fatpound::starrealm::entity
{
    Star::Star(const Descriptor& desc)
        :
        radiuses_(desc.radiuses),
        position_(desc.position),
        rotation_speed_(desc.rotation_speed),
        roll_(0.0f)
    {

    }

    auto Star::Make(const RadiusPack& radiuses, const dx::XMFLOAT3& centre, std::size_t flare_count) -> std::vector<dx::XMFLOAT3>
    {
        std::vector<dx::XMFLOAT3> star;
        const std::size_t capacity = flare_count * 2u;

        star.reserve(capacity + 1u);

        const float dTheta = 2.0f * dx::XM_PI / static_cast<float>(capacity);

        for (std::size_t i = 0u; i < capacity; ++i)
        {
            const float rad = (i % 2u == 0u)
                ? radiuses.outer_radius
                : radiuses.inner_radius
                ;

            star.emplace_back(
                rad * std::cos(static_cast<float>(i) * dTheta) + centre.x,
                rad * std::sin(static_cast<float>(i) * dTheta) + centre.y,
                centre.z
            );
        }

        return star;
    }
    auto Star::MakeWithCentre(const RadiusPack& radiuses, const dx::XMFLOAT3& centre, std::size_t flare_count) -> std::vector<dx::XMFLOAT3>
    {
        auto star = Star::Make(radiuses, centre, flare_count);
        
        star.emplace_back(centre.x, centre.y, centre.z);

        return star;
    }

    auto Star::GetTransformXM() const noexcept -> dx::XMMATRIX
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

    auto Star::GetPosition() const noexcept -> dx::XMFLOAT3
    {
        return position_;
    }

    float Star::GetOuterRadius() const noexcept
    {
        return radiuses_.outer_radius;
    }

    bool Star::IsWithinArea(const dx::XMFLOAT3& position, const float& radius) const noexcept
    {
        const dx::XMVECTOR& position_vec = dx::XMLoadFloat3(&position);
        const dx::XMVECTOR& this_pos_vec = dx::XMLoadFloat3(&this->position_);
        const dx::XMVECTOR& difference   = dx::XMVectorSubtract(this_pos_vec, position_vec);

        const float& length = dx::XMVectorGetX(dx::XMVector3Length(difference));

        return length < (this->radiuses_.outer_radius + radius);
    }
}