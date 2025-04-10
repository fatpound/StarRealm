module;

#include <FatNamespaces.hpp>

#include <DirectXMath.h>

export module StarRealm.View.Camera;

import FatPound.IO;

import std;

export namespace starrealm::view
{
    class Camera final
    {
    public:
        explicit Camera(const float max_depth, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept;

        explicit Camera()                  = delete;
        explicit Camera(const Camera&)     = delete;
        explicit Camera(Camera&&) noexcept = delete;

        auto operator = (const Camera&)     -> Camera& = delete;
        auto operator = (Camera&&) noexcept -> Camera& = delete;
        ~Camera() noexcept                             = default;


    public:
        auto GetMatrix() const noexcept -> ::DirectX::XMMATRIX;

        auto GetR() const noexcept -> float;
        auto GetX() const noexcept -> float;
        auto GetY() const noexcept -> float;
        auto GetZ() const noexcept -> float;

        void SetR(float r) noexcept;
        void SetX(float x) noexcept;
        void SetY(float y) noexcept;
        void SetZ(float z) noexcept;

        void Update() noexcept;
        void Reset() noexcept;


    protected:


    private:
        class Controller_ final
        {
        public:
            explicit Controller_(Camera& camera, std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard, std::shared_ptr<FATSPACE_IO::Mouse> pMouse) noexcept;

            explicit Controller_()                       = delete;
            explicit Controller_(const Controller_&)     = delete;
            explicit Controller_(Controller_&&) noexcept = delete;

            auto operator = (const Controller_&)     -> Controller_& = delete;
            auto operator = (Controller_&&) noexcept -> Controller_& = delete;
            ~Controller_() noexcept                                  = default;

        public:
            void Update() noexcept;

        protected:

        private:
            static constexpr auto scx_zoomIncrement_ = 0.02f;

        private:
            ::DirectX::XMFLOAT2 m_last_position_{};

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
