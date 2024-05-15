module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Camera;

export namespace fatpound::win32::d3d11
{
    class Camera final
    {
    public:
        Camera(const float& min_depth, const float& max_depth) noexcept;


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
        void Reset() noexcept;


    protected:


    private:
        const float& min_depth_;
        const float& max_depth_;

        float r_  = 0.1f;

        float x_  = 0.0f;
        float y_  = 0.0f;
        float z_  = 0.0f;
    };
}