module;

#include "../Win32_/FatWin32_Settings.hpp"
#include "../Win32_/FatWin32_Namespaces.hpp"

#include <DirectXMath.h>

module FatPound.Util.Camera;

namespace dx = DirectX;

namespace fatpound::util
{
    // Camera

    Camera::Camera(const float& min_depth, const float& max_depth, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& kbd) noexcept
        :
        min_depth_(min_depth),
        max_depth_(max_depth),
        mouse_(mouse),
        kbd_(kbd),
        controller_(*this)
    {

    }

    auto Camera::GetMatrix() const noexcept -> dx::XMMATRIX
    {
        const auto& look =
            dx::XMMatrixTranslation(x_, y_, z_) *
            dx::XMMatrixLookAtLH(
                dx::XMVectorSet(0.0f, 0.0f, -r_, 0.0f),        // position to go n look from
                dx::XMVectorSet(0.0f, 0.0f, max_depth_, 0.0f), // position to go n look at
                dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)        // y should be pointing towards up
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

    void Camera::Update([[maybe_unused]] float delta_time) noexcept
    {
        controller_.Update(delta_time);
    }

    void Camera::Reset() noexcept
    {
        r_ = 0.1f;

        x_ = 0.0f;
        y_ = 0.0f;
        z_ = 0.0f;
    }

    // Camera::Controller

    Camera::Controller::Controller(Camera& camera)
        :
        last_position_{ 0.0f, 0.0f },
        camera_(camera)
    {

    }

    void Camera::Controller::Update([[maybe_unused]] float delta_time)
    {
        if (camera_.kbd_.KeyIsPressed('R'))
        {
            camera_.Reset();
        }

        while (not camera_.mouse_.EventBufferIsEmpty())
        {
            const auto& mouse_event = camera_.mouse_.ReadFromBuffer();

            switch (mouse_event.GetType())
            {
            case NAMESPACE_IO::Mouse::Event::Type::LPress:
            {
                engaged_ = true;
                const auto& pos = mouse_event.GetPos();
                last_position_ = { static_cast<float>(pos.first), static_cast<float>(pos.second) };
            }
                break;

            case NAMESPACE_IO::Mouse::Event::Type::LRelease:
                engaged_ = false;
                break;

            case NAMESPACE_IO::Mouse::Event::Type::WheelUp:
                camera_.SetR(camera_.GetR() - zoom_increment_ * 5.0f);
                break;

            case NAMESPACE_IO::Mouse::Event::Type::WheelDown:
                camera_.SetR(camera_.GetR() + zoom_increment_ * 5.0f);
                break;

            default:
                break;
            }
        }

        if (engaged_)
        {
            dx::XMVECTOR lastPositionVec = dx::XMLoadFloat2(&last_position_);

            const auto& pos = camera_.mouse_.GetPos();
            dx::XMFLOAT2 currentPosition = { static_cast<float>(pos.first), static_cast<float>(pos.second) };

            dx::XMVECTOR currentPositionVec = dx::XMLoadFloat2(&currentPosition);
            dx::XMVECTOR deltaPositionVec = dx::XMVectorSubtract(currentPositionVec, lastPositionVec);

            deltaPositionVec = dx::XMVectorSetX(deltaPositionVec, -dx::XMVectorGetX(deltaPositionVec));

            camera_.SetX(camera_.GetX() + -dx::XMVectorGetX(deltaPositionVec) * zoom_increment_);
            camera_.SetY(camera_.GetY() + -dx::XMVectorGetY(deltaPositionVec) * zoom_increment_);

            last_position_ = currentPosition;
        }
    }
}