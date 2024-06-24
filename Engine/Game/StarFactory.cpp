module;

#include <DirectXMath.h>

#include <algorithm>

module StarRealm.StarFactory;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    auto StarFactory::GetStars() && -> std::vector<std::unique_ptr<entity::Star>>&&
    {
        return std::move(stars_);
    }

    auto StarFactory::operator () () -> std::unique_ptr<entity::Star>
    {
        entity::Star::RadiusPack radiuses;
        dx::XMFLOAT3 position;

        while (true)
        {
            radiuses = entity::Star::RadiusPack(outer_rad_dist_(rng_), inner_rad_dist_(rng_));
            position = dx::XMFLOAT3(x_dist_(rng_), y_dist_(rng_), zed_depth_dist_(rng_));

            if (std::ranges::none_of(stars_, [&](const auto& pstar) constexpr -> bool { return pstar->IsWithinArea(position, radiuses.outer_radius); }))
            {
                break;
            }
        }

        const entity::Star::Descriptor desc{
            position,
            radiuses,
            static_cast<std::size_t>(flare_count_dist_(rng_)),
            rotation_speed_dist_(rng_)
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
}