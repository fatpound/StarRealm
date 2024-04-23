module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module CameraController;

import Camera;
import Keyboard;
import Mouse;

export namespace fatpound::starrealm
{
    class CameraController final
    {
    public:
        CameraController(fatpound::win32::io::Mouse& mouse, const fatpound::win32::io::Keyboard& kbd, Camera& camera);


    public:
        void Update([[maybe_unused]] float delta_time);


    protected:


    private:
        Camera& camera_;

        fatpound::win32::io::Mouse& mouse_;
        const fatpound::win32::io::Keyboard& kbd_;

        DirectX::XMFLOAT2 last_position_ = { 0.0f, 0.0f };

        bool engaged_ = false;

        static constexpr float zoom_increment_ = 0.01f;
    };
}