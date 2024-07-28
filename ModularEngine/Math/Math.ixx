module;

#include <DirectXMath.h>

export module FatPound.Math;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;

    auto GetDifferenceVector(const DirectX::XMVECTOR& pos1_vec, const DirectX::XMVECTOR& pos2_vec) -> DirectX::XMVECTOR;

    float GetDistanceBetweenXMF3(const DirectX::XMFLOAT3& pos1, const DirectX::XMFLOAT3& pos2);
}