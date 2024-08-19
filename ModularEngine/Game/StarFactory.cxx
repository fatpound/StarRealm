module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#include <algorithm>

module StarRealm:StarFactory;

namespace dx = DirectX;

namespace starrealm
{
    StarFactory::StarFactory(NAMESPACE_D3D11::Graphics& gfx)
        :
        m_gfx_(gfx)
    {
        m_stars_.reserve(Settings::s_starCount);

        while (m_stars_.size() < Settings::s_starCount)
        {
            m_stars_.push_back(GenerateStar_());
        }
    }

    auto StarFactory::GetStars() && -> std::vector<std::unique_ptr<entity::Star>>&&
    {
        return std::move(m_stars_);
    }

    auto StarFactory::GenerateStar_() -> std::unique_ptr<entity::Star>
    {
        dx::XMFLOAT3 position{};
        entity::Star::RadiusPack radiusPack{};

        while (true)
        {
            position   = GeneratePosition3_();
            radiusPack = GenerateRadiusPack_();

            if (std::ranges::none_of(m_stars_, [&](const auto& pstar) -> bool { return pstar->IsWithinArea(position, radiusPack.outer_radius); }))
            {
                break;
            }
        }

        const auto& flareCount = static_cast<std::size_t>(m_flare_count_dist_(m_rng_));
        const auto& rotationSpeed = m_rotation_speed_dist_(m_rng_);

        const entity::Star::Descriptor& desc =
        {
            position,
            radiusPack,
            flareCount,
            rotationSpeed
        };

        switch (m_rng_() % 6u)
        {
        case 0:
            return std::make_unique<entity::star::HollowSingle>(m_gfx_, desc);

        case 1:
            return std::make_unique<entity::star::HollowMulti>(m_gfx_, desc);

        case 2:
            return std::make_unique<entity::star::HollowBlend>(m_gfx_, desc);

        case 3:
            return std::make_unique<entity::star::FilledSingle>(m_gfx_, desc);

        case 4:
            return std::make_unique<entity::star::FilledMulti>(m_gfx_, desc);

        case 5:
            return std::make_unique<entity::star::FilledBlend>(m_gfx_, desc);

        default:
            return nullptr;
        }
    }

    auto StarFactory::GenerateRadiusPack_() -> entity::Star::RadiusPack
    {
        const auto& outerRadius      = std::clamp(m_outer_rad_dist_(m_rng_),       Settings::s_minStarOuterRadius, Settings::s_maxStarOuterRadius);
        const auto& innerRadiusRatio = std::clamp(m_inner_rad_ratio_dist_(m_rng_), Settings::s_minStarInnerRatio,  Settings::s_maxStarInnerRatio);

        return { outerRadius, outerRadius * innerRadiusRatio };
    }

    auto StarFactory::GeneratePosition3_() -> ::DirectX::XMFLOAT3
    {
        const auto& z = m_z_dist_(m_rng_);

        if constexpr (s_distributeCircular_)
        {
            const auto& radius = std::sqrt(m_radius_dist_(m_rng_)) * Settings::s_worldRadiusFactor;
            const auto& angle = m_angle_dist_(m_rng_);

            const auto& x = radius * std::cos(angle) + m_normal_dist_(m_rng_);
            const auto& y = radius * std::sin(angle) + m_normal_dist_(m_rng_);

            return { x, y, z };
        }
        else
        {
            const auto& x = m_x_dist_(m_rng_);
            const auto& y = m_y_dist_(m_rng_);

            return { x, y, z };
        }
    }
}