module;

#include <DirectXMath.h>

module FatPound.Math;

namespace dx = DirectX;

namespace fatpound::math
{
    auto GetDifferenceVector(const ::dx::XMVECTOR pos1_vec, const ::dx::XMVECTOR pos2_vec) noexcept -> ::dx::XMVECTOR
    {
        return dx::XMVectorSubtract(pos1_vec, pos2_vec);
    }

    float GetDistanceBetweenXMF3(const ::dx::XMFLOAT3& pos1, const ::dx::XMFLOAT3& pos2) noexcept
    {
        const auto& pos1Vec = ::dx::XMLoadFloat3(&pos1);
        const auto& pos2Vec = ::dx::XMLoadFloat3(&pos2);

        return ::dx::XMVectorGetX(
            ::dx::XMVector3Length(GetDifferenceVector(pos1Vec, pos2Vec))
        );
    }
}