module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

module CameraController;

namespace dx = DirectX;

namespace fatpound::win32::d3d11
{
    CameraController::CameraController(fatpound::win32::io::Mouse& mouse, const fatpound::win32::io::Keyboard& kbd, Camera& camera)
        :
        mouse_(mouse),
        kbd_(kbd),
        camera_(camera)
    {

    }

    void CameraController::Update([[maybe_unused]] float delta_time)
    {
        if (kbd_.KeyIsPressed('R'))
        {
            camera_.Reset();
        }

        while (!mouse_.BufferIsEmpty())
        {
            const auto& mouse_event = mouse_.ReadFromBuffer();

            switch (mouse_event.GetType())
            {
            case fatpound::win32::io::Mouse::Event::Type::LPress:
            {
                engaged_ = true;
                const auto& pos = mouse_event.GetPos();
                last_position_ = { static_cast<float>(pos.first), static_cast<float>(pos.second) };
            }
                break;

            case fatpound::win32::io::Mouse::Event::Type::LRelease:
                engaged_ = false;
                break;

            case fatpound::win32::io::Mouse::Event::Type::WheelUp:
                camera_.SetR(camera_.GetR() - zoom_increment_ * 5.0f);
                break;

            case fatpound::win32::io::Mouse::Event::Type::WheelDown:
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