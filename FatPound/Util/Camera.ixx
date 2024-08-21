module;

#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module FatPound.Util.Camera;

export namespace fatpound::util
{
    class Camera final
    {
    public:
        explicit Camera(const float min_depth, const float max_depth) noexcept;

        explicit Camera() = delete;
        explicit Camera(const Camera& src) = delete;
        explicit Camera(Camera&& src) = delete;

        Camera& operator = (const Camera& src) = delete;
        Camera& operator = (Camera&& src) = delete;
        ~Camera() noexcept = default;


    public:
        auto operator <=> (const Camera& rhs) const = delete;
        bool operator ==  (const Camera& rhs) const = delete;


    public:
        auto GetMatrix() const noexcept -> ::DirectX::XMMATRIX;

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
        const float min_depth_;
        const float max_depth_;

        float r_  = 0.1f;
        float x_  = 0.0f;
        float y_  = 0.0f;
        float z_  = 0.0f;
    };
}