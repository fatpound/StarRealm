module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module Camera;

import D3D11Graphics;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    Camera::Camera(const float& min_depth, const float& max_depth) noexcept
        :
        min_depth_(min_depth),
        max_depth_(max_depth)
    {

    }

    dx::XMMATRIX Camera::GetMatrix() const noexcept
    {
        const auto& look =
            dx::XMMatrixTranslation(x_, y_, z_) *
            dx::XMMatrixLookAtLH(
                dx::XMVectorSet(0.0f, 0.0f, -r_, 0.0f),   // position to go n look from
                dx::XMVectorSet(0.0f, 0.0f, max_depth_, 0.0f), // position to go n look at
                dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) // y should be pointing towards up
        );

        return look;
    }

    float Camera::GetR() const noexcept
    {
        return r_;
    }
    float Camera::GetX() const noexcept
    {
        return x_;
    }
    float Camera::GetY() const noexcept
    {
        return y_;
    }
    float Camera::GetZ() const noexcept
    {
        return z_;
    }

    void Camera::SetR(float r) noexcept
    {
        r_ = r;
    }
    void Camera::SetX(float x) noexcept
    {
        x_ = x;
    }
    void Camera::SetY(float y) noexcept
    {
        y_ = y;
    }
    void Camera::SetZ(float z) noexcept
    {
        z_ = z;
    }

    void Camera::Reset() noexcept
    {
        r_ = 0.1f;

        x_ = 0.0f;
        y_ = 0.0f;
        z_ = 0.0f;
    }
}