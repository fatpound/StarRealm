module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Star;

import DrawableBase;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
#else
import <cmath>;
import <cstdint>;
/**/
import <vector>;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::starrealm
{
    class Star : public D3D11_NAMESPACE::DrawableBase<Star>
    {
    public:
        struct Descriptor final
        {
            const DirectX::XMFLOAT2& radius;
            const DirectX::XMFLOAT3& position;

            const std::size_t flare_count;

            const float rotation_speed;
        };


    public:
        Star(const Descriptor& desc);

        Star() = default;
        Star(const Star& src) = delete;
        Star& operator = (const Star& src) = delete;
        Star(Star&& src) = delete;
        Star& operator = (Star&& src) = delete;
        virtual ~Star() = default;


    public:
        static auto Make(const DirectX::XMFLOAT2& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;
        static auto MakeWithCentre(const DirectX::XMFLOAT2& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;


    public:
        virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override final;

        virtual void Update(float delta_time) noexcept override final;

        virtual auto GetPosition() const noexcept -> DirectX::XMFLOAT3 final;

        virtual float GetOuterRadius() const noexcept final;


    protected:
        DirectX::XMFLOAT2 radius_; // outer_radius, inner_radius

        DirectX::XMFLOAT3 position_;

        float rotation_speed_;
        float roll_;


    private:
    };
}