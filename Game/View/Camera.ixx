module;

#include <_macros/Namespaces.hxx>

export module StarRealm.View.Camera;

import <DirectXMath.h>;

import FatPound.IO;

import std;

namespace dx = DirectX;

export namespace starrealm::view
{
    class Camera final
    {
    public:
        explicit Camera(const float max_depth, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept
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

        explicit Camera()                  = delete;
        explicit Camera(const Camera&)     = delete;
        explicit Camera(Camera&&) noexcept = delete;

        auto operator = (const Camera&)     -> Camera& = delete;
        auto operator = (Camera&&) noexcept -> Camera& = delete;
        ~Camera() noexcept                             = default;


    public:
        auto GetMatrix() const noexcept -> dx::XMMATRIX
        {
            return
                dx::XMMatrixTranslation(m_x_, m_y_, m_z_) *
                dx::XMMatrixLookAtLH(
                    dx::XMVectorSet(0.0f, 0.0f, -m_r_, 0.0f),        // position to go n look from
                    dx::XMVectorSet(0.0f, 0.0f, mc_max_depth_, 0.0f), // position to go n look at
                    dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)        // y should be pointing towards up
                );
        }

        auto GetR() const noexcept -> float
        {
            return m_r_;
        }
        auto GetX() const noexcept -> float
        {
            return m_x_;
        }
        auto GetY() const noexcept -> float
        {
            return m_y_;
        }
        auto GetZ() const noexcept -> float
        {
            return m_z_;
        }

        void SetR(const float r) noexcept
        {
            m_r_ = r;
        }
        void SetX(const float x) noexcept
        {
            m_x_ = x;
        }
        void SetY(const float y) noexcept
        {
            m_y_ = y;
        }
        void SetZ(const float z) noexcept
        {
            m_z_ = z;
        }

        void Update() noexcept
        {
            m_controller_.Update();
        }
        void Reset() noexcept
        {
            static constexpr auto axis_reset_val = 0.0f;

            m_r_ = 0.1f;

            m_x_ = axis_reset_val;
            m_y_ = axis_reset_val;
            m_z_ = axis_reset_val;
        }


    protected:


    private:
        class Controller_ final
        {
            static constexpr auto scx_ZoomIncrement_ = 0.02f;

        public:
            explicit Controller_(Camera& camera, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept
                :
                m_camera_{ camera },
                mc_pKeyboard_{ pKeyboard },
                mc_pMouse_{ pMouse }
            {

            }

            explicit Controller_()                       = delete;
            explicit Controller_(const Controller_&)     = delete;
            explicit Controller_(Controller_&&) noexcept = delete;

            auto operator = (const Controller_&)     -> Controller_& = delete;
            auto operator = (Controller_&&) noexcept -> Controller_& = delete;
            ~Controller_() noexcept                                  = default;

        public:
            void Update() noexcept
            {
                if (mc_pKeyboard_->KeyIsPressed('R'))
                {
                    m_camera_.Reset();
                }

                while (not mc_pMouse_->EventBufferIsEmpty())
                {
                    const auto& mouseE = mc_pMouse_->GetEvent();

                    switch (mouseE->type)
                    {
                    case FATSPACE_IO::Mouse::Event::Type::LPress:
                    {
                        m_engaged_ = true;
        
                        m_last_position_ = dx::XMFLOAT2
                        {
                            static_cast<float>(mouseE->pos_x),
                            static_cast<float>(mouseE->pos_y)
                        };
                    }
                        break;
        
                    case FATSPACE_IO::Mouse::Event::Type::LRelease:
                        m_engaged_ = false;
                        break;

                    case FATSPACE_IO::Mouse::Event::Type::WheelUp:
                        m_camera_.SetR(m_camera_.GetR() - scx_ZoomIncrement_ * 5.0f);
                        break;

                    case FATSPACE_IO::Mouse::Event::Type::WheelDown:
                        m_camera_.SetR(m_camera_.GetR() + scx_ZoomIncrement_ * 5.0f);
                        break;
        
                    default:
                        break;
                    }
                }

                if (m_engaged_)
                {
                    const auto& pos = mc_pMouse_->GetPos();

                    const auto& lastPositionVec      = dx::XMLoadFloat2(&m_last_position_);
                    const auto& currentPosition      = dx::XMFLOAT2{ static_cast<float>(pos.first), static_cast<float>(pos.second) };
                                             
                    const auto& currentPositionVec   = dx::XMLoadFloat2(&currentPosition);
                    const auto& deltaPositionVec1    = dx::XMVectorSubtract(currentPositionVec, lastPositionVec);
                    const auto& deltaPositionVec2    = dx::XMVectorSetX(deltaPositionVec1, -dx::XMVectorGetX(deltaPositionVec1));

                    m_camera_.SetX(m_camera_.GetX() + -dx::XMVectorGetX(deltaPositionVec2) * scx_ZoomIncrement_);
                    m_camera_.SetY(m_camera_.GetY() + -dx::XMVectorGetY(deltaPositionVec2) * scx_ZoomIncrement_);

                    m_last_position_ = currentPosition;
                }
            }

        protected:

        private:
            dx::XMFLOAT2 m_last_position_{};

            Camera& m_camera_;

            const std::shared_ptr<FATSPACE_IO::Keyboard> mc_pKeyboard_;
            const std::shared_ptr<FATSPACE_IO::Mouse> mc_pMouse_;

            std::atomic<bool> m_engaged_{};
        };


    private:
        const float mc_max_depth_;

        float m_r_{ 0.1f };
        float m_x_{};
        float m_y_{};
        float m_z_{};

        Controller_ m_controller_;
    };
}
