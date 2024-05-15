module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module CameraController;

import Camera;
import Keyboard;
import Mouse;

export namespace fatpound::win32::d3d11
{
    class CameraController final
    {
    public:
        CameraController(Camera& camera, fatpound::win32::io::Mouse& mouse, const fatpound::win32::io::Keyboard& kbd);


    public:
        void Update([[maybe_unused]] float delta_time);


    protected:


    private:
        DirectX::XMFLOAT2 last_position_;

        Camera& camera_;

        fatpound::win32::io::Mouse& mouse_;
        const fatpound::win32::io::Keyboard& kbd_;

        bool engaged_ = false;

        static constexpr float zoom_increment_ = 0.01f;
    };
}