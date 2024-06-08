module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module FatPound.Util.CameraController;

import FatPound.Util.Camera;
import FatPound.Win32;

export namespace fatpound::util
{
    class CameraController final
    {
    public:
        CameraController(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& kbd);


    public:
        void Update([[maybe_unused]] float delta_time);


    protected:


    private:
        ::DirectX::XMFLOAT2 last_position_;

        Camera& camera_;

        NAMESPACE_IO::Mouse& mouse_;
        const NAMESPACE_IO::Keyboard& kbd_;

        bool engaged_ = false;

        static constexpr float zoom_increment_ = 0.01f;
    };
}