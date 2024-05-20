module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module CameraController;

namespace dx = DirectX;

namespace fatpound::win32::directx
{
    CameraController::CameraController(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& kbd)
        :
        last_position_{ 0.0f, 0.0f },
        camera_(camera),
        mouse_(mouse),
        kbd_(kbd)
    {

    }

    void CameraController::Update([[maybe_unused]] float delta_time)
    {
        if (kbd_.KeyIsPressed('R'))
        {
            camera_.Reset();
        }

        while (!mouse_.EventBufferIsEmpty())
        {
            const auto& mouse_event = mouse_.ReadFromBuffer();

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

            const auto& pos = mouse_.GetPos();
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