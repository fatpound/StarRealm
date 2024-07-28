module;

#include "../Win32_/FatWin32_Settings.hpp"
#include "../Win32_/FatWin32_Namespaces.hpp"

#include <DirectXMath.h>

export module FatPound.Util.Camera;

import FatPound.Win32;

export namespace fatpound::util
{
    class Camera final
    {
    public:
        class Controller final
        {
        public:
            Controller(Camera& camera);


        public:
            void Update([[maybe_unused]] float delta_time);


        protected:


        private:
            DirectX::XMFLOAT2 last_position_;

            Camera& camera_;

            bool engaged_ = false;

            static constexpr float zoom_increment_ = 0.01f;
        };


    public:
        Camera(
            const float& min_depth,
            const float& max_depth,
            NAMESPACE_IO::Mouse& mouse,
            const NAMESPACE_IO::Keyboard& kbd) noexcept;


    public:
        auto GetMatrix() const noexcept -> DirectX::XMMATRIX;

        float GetR() const noexcept;
        float GetX() const noexcept;
        float GetY() const noexcept;
        float GetZ() const noexcept;

        void SetR(float r) noexcept;
        void SetX(float x) noexcept;
        void SetY(float y) noexcept;
        void SetZ(float z) noexcept;

        void Update([[maybe_unused]] float delta_time) noexcept;
        void Reset() noexcept;


    protected:


    private:
        const float min_depth_;
        const float max_depth_;

        float r_  = 0.1f;
        float x_  = 0.0f;
        float y_  = 0.0f;
        float z_  = 0.0f;

        NAMESPACE_IO::Mouse& mouse_;
        const NAMESPACE_IO::Keyboard& kbd_;

        Controller controller_;
    };
}