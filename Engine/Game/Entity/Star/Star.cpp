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

    auto Star::GetTransformXM() const noexcept -> dx::XMMATRIX
    {
        const auto& pos_vec = dx::XMLoadFloat3(&position_);

        return dx::XMMatrixTranslationFromVector(dx::XMVectorNegate(pos_vec)) *
            dx::XMMatrixRotationZ(roll_) *
            dx::XMMatrixTranslationFromVector(pos_vec);
    }

    auto Star::GetPosition() const noexcept -> dx::XMFLOAT3
    {
        return position_;
    }

    float Star::GetOuterRadius() const noexcept
    {
        return radiuses_.outer_radius;
    }

    void Star::Update(float delta_time) noexcept
    {
        roll_ += (delta_time * rotation_speed_);
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