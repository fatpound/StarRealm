module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module Star;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    Star::Star(const Descriptor& desc)
        :
        radius_(desc.radius),
        position_(desc.position),
        rotation_speed_(desc.rotation_speed)
    {

    }

    dx::XMMATRIX Star::GetTransformXM() const noexcept
    {
        const auto& pos_vec = dx::XMLoadFloat3(&position_);

        return dx::XMMatrixTranslationFromVector(dx::XMVectorNegate(pos_vec)) *
            dx::XMMatrixRotationZ(roll_) *
            dx::XMMatrixTranslationFromVector(pos_vec);
    }

    dx::XMFLOAT3 Star::GetPosition() const noexcept
    {
        return position_;
    }

    float Star::GetOuterRadius() const noexcept
    {
        return radius_.x;
    }

    void Star::Update(float delta_time) noexcept
    {
        roll_ += (delta_time * rotation_speed_);
    }
}