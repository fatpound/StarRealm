module;

#include <DirectXMath.h>

export module FatPound.Math;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    template <Number N>
    inline consteval auto ConstevalSqrt(N num, N current, N prev) -> N
    {
        return current == prev ? current : ConstevalSqrt<N>(num, 0.5f * (current + num / current), current);
    }
    template <Number N>
    inline consteval auto ConstevalSqrt(N num) -> N
    {
        return (num >= 0.0f && num < std::numeric_limits<float>::infinity()) ? ConstevalSqrt<N>(num, num, 0.0f) : std::numeric_limits<float>::quiet_NaN();
    }

    auto GetDifferenceVector(const ::DirectX::XMVECTOR pos1_vec, const ::DirectX::XMVECTOR pos2_vec) noexcept -> ::DirectX::XMVECTOR;

    float GetDistanceBetweenXMF3(const ::DirectX::XMFLOAT3& pos1, const ::DirectX::XMFLOAT3& pos2) noexcept;
}