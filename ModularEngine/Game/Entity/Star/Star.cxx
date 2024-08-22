module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star;

namespace dx = DirectX;

namespace starrealm::entity
{
    Star::Star(const Descriptor& desc) noexcept
        :
        m_position_(desc.position),
        m_radiuses_(desc.radiuses),
        m_rotation_speed_(desc.rotation_speed),
        m_roll_(0.0f)
    {

    }

    auto Star::operator <=> (const Star& rhs) const noexcept
    {
        return m_radiuses_.outer_radius <=> rhs.m_radiuses_.outer_radius;
    }

    auto Star::GetTransformXM() const noexcept -> ::dx::XMMATRIX
    {
        const auto& pos_vec = ::dx::XMLoadFloat3(&m_position_);

        return ::dx::XMMatrixTranslationFromVector(::dx::XMVectorNegate(pos_vec)) *
            ::dx::XMMatrixRotationZ(m_roll_) *
            ::dx::XMMatrixTranslationFromVector(pos_vec);
    }

    auto Star::GetPosition() const noexcept -> ::dx::XMFLOAT3
    {
        return m_position_;
    }

    float Star::GetOuterRadius() const noexcept
    {
        return m_radiuses_.outer_radius;
    }

    void Star::Update(const float delta_time) noexcept
    {
        m_roll_ += (delta_time * m_rotation_speed_);
    }

    bool Star::IsWithinArea(const ::dx::XMFLOAT3& position, const float radius) const noexcept
    {
        const float distance = NAMESPACE_MATH::GetDistanceBetweenXMF3(this->m_position_, position);
        const float radsum = m_radiuses_.outer_radius + radius;

        return radsum > distance;
    }
}