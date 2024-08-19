module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module StarRealm:StarFactory;

import StarRealm.Entity;

import FatPound;

import std;

export namespace starrealm
{
    class StarFactory final
    {
    public:
        struct Settings final
        {
            static constexpr auto s_starCount = 1000u;
            static constexpr auto s_minFlareCount = 2u;
            static constexpr auto s_maxFlareCount = 7u;

            static constexpr auto s_worldWidth  = 40.0f;
            static constexpr auto s_worldHeight = 40.0f;

            static constexpr auto s_worldDensityFactor = 1.0f;
            static constexpr auto s_worldArea = s_worldDensityFactor * static_cast<float>(s_starCount);
            static constexpr auto s_meanWorldRadius = 0.1f;
            static constexpr auto s_devWorldRadius = std::min(s_worldWidth, s_worldHeight) * 2.0f;
            static constexpr auto s_worldRadiusFactor = NAMESPACE_MATH::ConstevalSqrt<decltype(s_worldArea)>(s_worldArea / std::numbers::pi_v<float>);

            static constexpr auto s_meanStarOuterRadius = 0.6f;
            static constexpr auto s_devStarOuterRadius  = 0.7f;
            static constexpr auto s_minStarOuterRadius  = 0.5f;
            static constexpr auto s_maxStarOuterRadius  = 1.0f;

            static constexpr auto s_meanStarInnerRatio = 0.4f;
            static constexpr auto s_devStarInnerRatio  = 0.25f;
            static constexpr auto s_minStarInnerRatio  = 0.2f;
            static constexpr auto s_maxStarInnerRatio  = 0.5f;

            static constexpr auto s_minStarDepth = 0.1f;
            static constexpr auto s_maxStarDepth = 20.0f;

            static constexpr auto s_minRotationSpeed = -1.5f * std::numbers::pi_v<float>;
            static constexpr auto s_maxRotationSpeed =  1.5f * std::numbers::pi_v<float>;
        };


    public:
        explicit StarFactory(NAMESPACE_D3D11::Graphics& gfx);

        explicit StarFactory() = delete;
        explicit StarFactory(const StarFactory& src) = delete;
        explicit StarFactory(StarFactory&& src) = delete;

        StarFactory& operator = (const StarFactory& src) = delete;
        StarFactory& operator = (StarFactory&& src) = delete;
        ~StarFactory() noexcept = default;


    public:
        auto GetStars() && noexcept -> std::vector<std::unique_ptr<entity::Star>>&&;


    protected:


    private:
        auto GenerateStar_() -> std::unique_ptr<entity::Star>;

        auto GenerateRadiusPack_() -> entity::Star::RadiusPack;

        auto GeneratePosition3_() -> ::DirectX::XMFLOAT3;


    private:
        NAMESPACE_D3D11::Graphics& m_gfx_;

        std::minstd_rand m_rng_{ std::random_device{}() };

        std::uniform_real_distribution<float> m_x_dist_{ -Settings::s_worldWidth,   Settings::s_worldWidth };
        std::uniform_real_distribution<float> m_y_dist_{ -Settings::s_worldHeight,  Settings::s_worldHeight };
        std::uniform_real_distribution<float> m_z_dist_{  Settings::s_minStarDepth, Settings::s_maxStarDepth };

        std::uniform_real_distribution<float> m_rotation_speed_dist_{ Settings::s_minRotationSpeed, Settings::s_maxRotationSpeed };
        std::uniform_real_distribution<float> m_angle_dist_{ 0.0f, 2.0f * std::numbers::pi_v<float> };

        std::uniform_int_distribution<int> m_flare_count_dist_{ Settings::s_minFlareCount, Settings::s_maxFlareCount };

        std::normal_distribution<float> m_outer_rad_dist_{ Settings::s_meanStarOuterRadius, Settings::s_devStarOuterRadius };
        std::normal_distribution<float> m_inner_rad_ratio_dist_{ Settings::s_meanStarInnerRatio, Settings::s_devStarInnerRatio };
        std::normal_distribution<float> m_radius_dist_{ Settings::s_meanWorldRadius, Settings::s_devWorldRadius };
        std::normal_distribution<float> m_normal_dist_{ 0.0f, 1.0f };

        std::vector<std::unique_ptr<entity::Star>> m_stars_;

        static constexpr bool s_distributeCircular_ = true;
    };
}