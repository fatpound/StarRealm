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
        gfx_(gfx)
    {
        stars_.reserve(Settings::starCount);

        while (stars_.size() < Settings::starCount)
        {
            stars_.push_back(GenerateStar_());
        }
    }

    auto StarFactory::GetStars() && -> std::vector<std::unique_ptr<entity::Star>>&&
    {
        return std::move(stars_);
    }

    auto StarFactory::GenerateStar_() -> std::unique_ptr<entity::Star>
    {
        dx::XMFLOAT3 position;
        entity::Star::RadiusPack radiusPack;

        while (true)
        {
            position   = GeneratePosition3_();
            radiusPack = GenerateRadiusPack_();

            if (std::ranges::none_of(stars_, [&](const auto& pstar) -> bool { return pstar->IsWithinArea(position, radiusPack.outer_radius); }))
            {
                break;
            }
        }

        const auto& flareCount = static_cast<std::size_t>(flare_count_dist_(rng_));
        const auto& rotationSpeed = rotation_speed_dist_(rng_);

        const entity::Star::Descriptor& desc =
        {
            position,
            radiusPack,
            flareCount,
            rotationSpeed
        };

        switch (rng_() % 6u)
        {
        case 0:
            return std::make_unique<entity::star::HollowSingle>(gfx_, desc);

        case 1:
            return std::make_unique<entity::star::HollowMulti>(gfx_, desc);

        case 2:
            return std::make_unique<entity::star::HollowBlend>(gfx_, desc);

        case 3:
            return std::make_unique<entity::star::FilledSingle>(gfx_, desc);

        case 4:
            return std::make_unique<entity::star::FilledMulti>(gfx_, desc);

        case 5:
            return std::make_unique<entity::star::FilledBlend>(gfx_, desc);

        default:
            return nullptr;
        }
    }

    auto StarFactory::GenerateRadiusPack_() -> entity::Star::RadiusPack
    {
        const auto& outerRadius      = std::clamp(outer_rad_dist_(rng_),       Settings::minStarOuterRadius, Settings::maxStarOuterRadius);
        const auto& innerRadiusRatio = std::clamp(inner_rad_ratio_dist_(rng_), Settings::minStarInnerRatio,  Settings::maxStarInnerRatio);

        return { outerRadius, outerRadius * innerRadiusRatio };
    }

    auto StarFactory::GeneratePosition3_() -> ::DirectX::XMFLOAT3
    {
        const auto& z = z_dist_(rng_);

        if constexpr (StarFactory::distribute_circular_)
        {
            const auto& maxWorldRadius = std::max(Settings::worldWidth, Settings::worldHeight) * 0.5f;

            const auto& worldRadius = std::sqrt(world_radius_dist_(rng_)) * maxWorldRadius;
            const auto& angle = angle_dist_(rng_);

            const auto& x = worldRadius * std::cos(angle) + normal_dist_(rng_);
            const auto& y = worldRadius * std::sin(angle) + normal_dist_(rng_);

            return { x, y, z };
        }
        else
        {
            const auto& x = x_dist_(rng_);
            const auto& y = y_dist_(rng_);

            return { x, y, z };
        }
    }
}