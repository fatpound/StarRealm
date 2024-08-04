module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module FatPound.Util.CameraController;

namespace dx = DirectX;

namespace fatpound::util
{
    CameraController::CameraController(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard)
        :
        camera_(camera),
        mouse_(mouse),
        keyboard_(keyboard)
    {

    }

    void CameraController::Update()
    {
        if (keyboard_.KeyIsPressed('R'))
        {
            camera_.Reset();
        }

        while (not mouse_.EventBufferIsEmpty())
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
                camera_.SetR(camera_.GetR() - s_zoomIncrement_ * 5.0f);
                break;

            case NAMESPACE_IO::Mouse::Event::Type::WheelDown:
                camera_.SetR(camera_.GetR() + s_zoomIncrement_ * 5.0f);
                break;

            case NAMESPACE_IO::Mouse::Event::Type::RPress:       [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::RRelease:     [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::WheelPress:   [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::WheelRelease: [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::Enter:        [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::Move:         [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::Leave:        [[fallthrough]];
            case NAMESPACE_IO::Mouse::Event::Type::Invalid:      [[fallthrough]];

            default:
                break;
            }
        }

        if (engaged_)
        {
            ::dx::XMVECTOR lastPositionVec = ::dx::XMLoadFloat2(&last_position_);

            const auto& pos = mouse_.GetPos();
            ::dx::XMFLOAT2 currentPosition = { static_cast<float>(pos.first), static_cast<float>(pos.second) };

            ::dx::XMVECTOR currentPositionVec = ::dx::XMLoadFloat2(&currentPosition);
            ::dx::XMVECTOR deltaPositionVec   = ::dx::XMVectorSubtract(currentPositionVec, lastPositionVec);

            deltaPositionVec = ::dx::XMVectorSetX(deltaPositionVec, -::dx::XMVectorGetX(deltaPositionVec));

            camera_.SetX(camera_.GetX() + -::dx::XMVectorGetX(deltaPositionVec) * s_zoomIncrement_);
            camera_.SetY(camera_.GetY() + -::dx::XMVectorGetY(deltaPositionVec) * s_zoomIncrement_);

            last_position_ = currentPosition;
        }
    }
}