module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module StarRealm:StarFactory;

export import StarRealm.Entity;

import FatPound;

import std;

namespace dx = DirectX;

export namespace starrealm
{
    template
    <
        std::integral size_t = unsigned int,
        std::floating_point float_t = float
    >
    class StarFactory final
    {
        using unique_pstar = std::unique_ptr<entity::Star>;

    public:
        struct Settings final
        {
            size_t m_starCount = 1000u;
            size_t m_minFlareCount = 2u;
            size_t m_maxFlareCount = 7u;

            float_t m_worldWidth  = 40.0f;
            float_t m_worldHeight = 40.0f;

            float_t m_worldDensityFactor = 1.0f;
            float_t m_worldArea = m_worldDensityFactor * static_cast<float_t>(m_starCount);
            float_t m_meanWorldRadius = 0.1f;
            float_t m_devWorldRadius = std::min(m_worldWidth, m_worldHeight) * 2.0f;
            float_t m_worldRadiusFactor = std::sqrt(m_worldArea / std::numbers::pi_v<float_t>);

            float_t m_meanStarOuterRadius = 0.6f;
            float_t m_devStarOuterRadius  = 0.7f;
            float_t m_minStarOuterRadius  = 0.5f;
            float_t m_maxStarOuterRadius  = 1.0f;

            float_t m_meanStarInnerRatio = 0.4f;
            float_t m_devStarInnerRatio  = 0.25f;
            float_t m_minStarInnerRatio  = 0.2f;
            float_t m_maxStarInnerRatio  = 0.5f;

            float_t m_minStarDepth = 0.1f;
            float_t m_maxStarDepth = 20.0f;

            float_t m_minRotationSpeed = -1.5f * std::numbers::pi_v<float_t>;
            float_t m_maxRotationSpeed =  1.5f * std::numbers::pi_v<float_t>;
        };


    public:
        explicit StarFactory(NAMESPACE_D3D11::Graphics<>& gfx)
            :
            StarFactory(gfx, Settings{})
        {

        }
        explicit StarFactory(NAMESPACE_D3D11::Graphics<>& gfx, const Settings& settings)
            :
            m_gfx_(gfx),
            m_settings_{ settings }
        {
            m_stars_.reserve(m_settings_.m_starCount);

            while (m_stars_.size() < m_settings_.m_starCount)
            {
                m_stars_.push_back(GenerateStar_());
            }
        }

        explicit StarFactory() = delete;
        explicit StarFactory(const StarFactory& src) = delete;
        explicit StarFactory(StarFactory&& src) = delete;

        auto operator = (const StarFactory& src) -> StarFactory& = delete;
        auto operator = (StarFactory&& src)      -> StarFactory& = delete;
        ~StarFactory() noexcept = default;


    public:
        auto GetStars() &  noexcept -> auto
        {
            return m_stars_;
        }
        auto GetStars() && noexcept -> auto&&
        {
            return std::move(m_stars_);
        }


    protected:


    private:
        auto GenerateStar_() -> unique_pstar
        {
            dx::XMFLOAT3 position{};
            entity::Star::RadiusPack radiusPack{};

            while (true)
            {
                position = GeneratePosition3_();
                radiusPack = GenerateRadiusPack_();

                if (std::ranges::none_of(m_stars_, [&](const auto& pstar) noexcept -> bool { return pstar->IsWithinArea(position, radiusPack.outer_radius); }))
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

        auto GenerateRadiusPack_() -> entity::Star::RadiusPack
        {
            const auto& outerRadius = std::clamp(m_outer_rad_dist_(m_rng_), m_settings_.m_minStarOuterRadius, m_settings_.m_maxStarOuterRadius);
            const auto& innerRadiusRatio = std::clamp(m_inner_rad_ratio_dist_(m_rng_), m_settings_.m_minStarInnerRatio, m_settings_.m_maxStarInnerRatio);

            return { outerRadius, outerRadius * innerRadiusRatio };
        }

        auto GeneratePosition3_() -> ::DirectX::XMFLOAT3
        {
            const auto& z = m_z_dist_(m_rng_);

            if constexpr (s_distributeCircular_)
            {
                const auto& radius = std::sqrt(m_radius_dist_(m_rng_)) * m_settings_.m_worldRadiusFactor;
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


    private:
        NAMESPACE_D3D11::Graphics<>& m_gfx_;

        const Settings m_settings_;

        std::minstd_rand m_rng_{ std::random_device{}() };

        std::uniform_real_distribution<float_t> m_x_dist_{ -m_settings_.m_worldWidth,   m_settings_.m_worldWidth   };
        std::uniform_real_distribution<float_t> m_y_dist_{ -m_settings_.m_worldHeight,  m_settings_.m_worldHeight  };
        std::uniform_real_distribution<float_t> m_z_dist_{  m_settings_.m_minStarDepth, m_settings_.m_maxStarDepth };

        std::uniform_real_distribution<float_t> m_rotation_speed_dist_{ m_settings_.m_minRotationSpeed, m_settings_.m_maxRotationSpeed };
        std::uniform_real_distribution<float_t> m_angle_dist_{ 0.0f, 2.0f * std::numbers::pi_v<float_t> };

        std::uniform_int_distribution<size_t> m_flare_count_dist_{ m_settings_.m_minFlareCount, m_settings_.m_maxFlareCount };

        std::normal_distribution<float_t> m_outer_rad_dist_{ m_settings_.m_meanStarOuterRadius, m_settings_.m_devStarOuterRadius };
        std::normal_distribution<float_t> m_inner_rad_ratio_dist_{ m_settings_.m_meanStarInnerRatio, m_settings_.m_devStarInnerRatio };
        std::normal_distribution<float_t> m_radius_dist_{ m_settings_.m_meanWorldRadius, m_settings_.m_devWorldRadius };
        std::normal_distribution<float_t> m_normal_dist_{ 0.0f, 1.0f };

        std::vector<unique_pstar> m_stars_;

        static constexpr bool s_distributeCircular_ = true;
    };
}