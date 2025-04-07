module;

#include <FatNamespaces.hpp>

#include <DirectXMath.h>

module StarRealm.View.Camera;

namespace dx = DirectX;

namespace starrealm::view
{
    // Camera

    Camera::Camera(const float max_depth, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept
        :
        mc_max_depth_{ max_depth },
        ///////////////////////////////////////
#pragma region(disabled C4355)
#pragma warning (push)
#pragma warning (disable : 4355)
        m_controller_(*this, pKeyboard, pMouse)
#pragma warning (pop)
#pragma endregion
        ///////////////////////////////////////
    {
        
    }

    auto Camera::GetMatrix() const noexcept -> ::dx::XMMATRIX
    {
        const auto& look =
            ::dx::XMMatrixTranslation(m_x_, m_y_, m_z_) *
            ::dx::XMMatrixLookAtLH(
                ::dx::XMVectorSet(0.0f, 0.0f, -m_r_, 0.0f),        // position to go n look from
                ::dx::XMVectorSet(0.0f, 0.0f, mc_max_depth_, 0.0f), // position to go n look at
                ::dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)        // y should be pointing towards up
        );

        return look;
    }

    auto Camera::GetR() const noexcept -> float
    {
        return m_r_;
    }
    auto Camera::GetX() const noexcept -> float
    {
        return m_x_;
    }
    auto Camera::GetY() const noexcept -> float
    {
        return m_y_;
    }
    auto Camera::GetZ() const noexcept -> float
    {
        return m_z_;
    }

    void Camera::SetR(float r) noexcept
    {
        m_r_ = r;
    }
    void Camera::SetX(float x) noexcept
    {
        m_x_ = x;
    }
    void Camera::SetY(float y) noexcept
    {
        m_y_ = y;
    }
    void Camera::SetZ(float z) noexcept
    {
        m_z_ = z;
    }

    void Camera::Update() noexcept
    {
        m_controller_.Update();
    }
    void Camera::Reset() noexcept
    {
        static constexpr auto axis_reset_val = 0.0f;

        m_r_ = 0.1f;

        m_x_ = axis_reset_val;
        m_y_ = axis_reset_val;
        m_z_ = axis_reset_val;
    }


    // Camera::Controller_

    Camera::Controller_::Controller_(Camera& camera, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept
        :
        m_camera_{ camera },
        mc_pKeyboard_{ pKeyboard },
        mc_pMouse_{ pMouse }
    {

    }

    void Camera::Controller_::Update() noexcept
    {
        if (mc_pKeyboard_->KeyIsPressed('R'))
        {
            m_camera_.Reset();
        }

        while (not mc_pMouse_->EventBufferIsEmpty())
        {
            auto mouseE = mc_pMouse_->GetEvent();

            switch (mouseE->type)
            {
            case FATSPACE_IO::MouseEvent::Type::LPress:
            {
                m_engaged_ = true;
        
                m_last_position_ = ::DirectX::XMFLOAT2
                {
                    static_cast<float>(mouseE->pos_x),
                    static_cast<float>(mouseE->pos_y)
                };
            }
                break;
        
            case FATSPACE_IO::MouseEvent::Type::LRelease:
                m_engaged_ = false;
                break;
        

            case FATSPACE_IO::MouseEvent::Type::WheelUp:
                m_camera_.SetR(m_camera_.GetR() - scx_zoomIncrement_ * 5.0f);
                break;

            case FATSPACE_IO::MouseEvent::Type::WheelDown:
                m_camera_.SetR(m_camera_.GetR() + scx_zoomIncrement_ * 5.0f);
                break;
        
            default:
                break;
            }
        }

        if (m_engaged_)
        {
            const auto& pos = mc_pMouse_->GetPos();

            const auto& lastPositionVec = ::dx::XMLoadFloat2(&m_last_position_);
            const auto& currentPosition = ::dx::XMFLOAT2{ static_cast<float>(pos.first), static_cast<float>(pos.second) };

            const auto& currentPositionVec = ::dx::XMLoadFloat2(&currentPosition);
            auto deltaPositionVec = ::dx::XMVectorSubtract(currentPositionVec, lastPositionVec);

            deltaPositionVec = ::dx::XMVectorSetX(deltaPositionVec, -::dx::XMVectorGetX(deltaPositionVec));

            m_camera_.SetX(m_camera_.GetX() + -::dx::XMVectorGetX(deltaPositionVec) * scx_zoomIncrement_);
            m_camera_.SetY(m_camera_.GetY() + -::dx::XMVectorGetY(deltaPositionVec) * scx_zoomIncrement_);

            m_last_position_ = currentPosition;
        }
    }
}
