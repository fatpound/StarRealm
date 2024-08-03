module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm:StarFactory;

export import StarRealm.Entity;

import FatPound;

import std;

export namespace starrealm
{
    class StarFactory final
    {
    public:
        struct Settings final
        {
            static constexpr auto s_starCount = 200u;
            static constexpr auto s_minFlareCount = 2u;
            static constexpr auto s_maxFlareCount = 7u;

            static constexpr auto s_worldWidth = 16.0f;
            static constexpr auto s_worldHeight = 9.0f;

            static constexpr auto s_worldDensityFactor = 1.0f;
            static constexpr auto s_worldArea = s_worldDensityFactor * static_cast<float>(s_starCount);
            static constexpr auto s_maxWorldRadius = NAMESPACE_MATH::ConstevalSqrt<decltype(s_worldArea)>(s_worldArea / std::numbers::pi_v<float>);

            static constexpr auto s_meanStarOuterRadius = 0.6f;
            static constexpr auto s_devStarOuterRadius  = 0.7f;
            static constexpr auto s_minStarOuterRadius  = 0.5f;
            static constexpr auto s_maxStarOuterRadius  = 1.0f;

            static constexpr auto s_meanStarInnerRatio = 0.4f;
            static constexpr auto s_devStarInnerRatio  = 0.25f;
            static constexpr auto s_minStarInnerRatio  = 0.2f;
            static constexpr auto s_maxStarInnerRatio  = 0.5f;

            static constexpr auto s_minStarDepth = 0.25f;
            static constexpr auto s_maxStarDepth = 10.0f;

            static constexpr auto s_minRotationSpeed = -1.0f * std::numbers::pi_v<float>;
            static constexpr auto s_maxRotationSpeed =  1.0f * std::numbers::pi_v<float>;
        };


    public:
        StarFactory(NAMESPACE_D3D11::Graphics& gfx);

        StarFactory() = delete;
        StarFactory(const StarFactory& src) = delete;
        StarFactory& operator = (const StarFactory& src) = delete;

        StarFactory(StarFactory&& src) = delete;
        StarFactory& operator = (StarFactory&& src) = delete;
        ~StarFactory() noexcept = default;


    public:
        auto GetStars() && -> std::vector<std::unique_ptr<entity::Star>>&&;


    protected:


    private:
        auto GenerateStar_() -> std::unique_ptr<entity::Star>;

        auto GenerateRadiusPack_() -> entity::Star::RadiusPack;

        auto GeneratePosition3_() -> ::DirectX::XMFLOAT3;


    private:
        NAMESPACE_D3D11::Graphics& gfx_;

        std::minstd_rand rng_{ std::random_device{}() };

        std::uniform_real_distribution<float> x_dist_{ -Settings::s_worldWidth,   Settings::s_worldWidth };
        std::uniform_real_distribution<float> y_dist_{ -Settings::s_worldHeight,  Settings::s_worldHeight };
        std::uniform_real_distribution<float> z_dist_{  Settings::s_minStarDepth, Settings::s_maxStarDepth };

        std::uniform_real_distribution<float> rotation_speed_dist_{ Settings::s_minRotationSpeed, Settings::s_maxRotationSpeed };
        std::uniform_real_distribution<float> world_radius_dist_{ 0.0f, std::min(Settings::s_worldWidth, Settings::s_worldHeight) * std::numbers::pi_v<float> };
        std::uniform_real_distribution<float> angle_dist_{ 0.0f, 2.0f * std::numbers::pi_v<float> };

        std::uniform_int_distribution<int> flare_count_dist_{ Settings::s_minFlareCount, Settings::s_maxFlareCount };

        std::normal_distribution<float> outer_rad_dist_{ Settings::s_meanStarOuterRadius, Settings::s_devStarOuterRadius };
        std::normal_distribution<float> inner_rad_ratio_dist_{ Settings::s_meanStarInnerRatio,  Settings::s_devStarInnerRatio };
        std::normal_distribution<float> normal_dist_{ 0.0f, 1.0f };

        std::vector<std::unique_ptr<entity::Star>> stars_;

        static constexpr bool s_distributeCircular_ = true;
    };
}