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
            static constexpr auto starCount = 200u;
            static constexpr auto minFlareCount = 2u;
            static constexpr auto maxFlareCount = 7u;

            static constexpr auto worldWidth = 16.0f;
            static constexpr auto worldHeight = 9.0f;

            static constexpr auto worldDensityFactor = 1.0f;
            static constexpr auto worldArea = worldDensityFactor * static_cast<float>(Settings::starCount);
            static constexpr auto maxWorldRadius = NAMESPACE_MATH::ConstevalSqrt<decltype(Settings::worldArea)>(Settings::worldArea / std::numbers::pi_v<float>);

            static constexpr auto meanStarOuterRadius = 0.6f;
            static constexpr auto devStarOuterRadius  = 0.7f;
            static constexpr auto minStarOuterRadius  = 0.5f;
            static constexpr auto maxStarOuterRadius  = 1.0f;

            static constexpr auto meanStarInnerRatio = 0.4f;
            static constexpr auto devStarInnerRatio  = 0.25f;
            static constexpr auto minStarInnerRatio  = 0.2f;
            static constexpr auto maxStarInnerRatio  = 0.5f;

            static constexpr auto minStarDepth = 0.25f;
            static constexpr auto maxStarDepth = 10.0f;

            static constexpr auto minRotationSpeed = -1.0f * std::numbers::pi_v<float>;
            static constexpr auto maxRotationSpeed =  1.0f * std::numbers::pi_v<float>;
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

        std::uniform_real_distribution<float> x_dist_{ -Settings::worldWidth,   Settings::worldWidth };
        std::uniform_real_distribution<float> y_dist_{ -Settings::worldHeight,  Settings::worldHeight };
        std::uniform_real_distribution<float> z_dist_{  Settings::minStarDepth, Settings::maxStarDepth };

        std::uniform_real_distribution<float> rotation_speed_dist_{ Settings::minRotationSpeed, Settings::maxRotationSpeed };
        std::uniform_real_distribution<float> world_radius_dist_{ 0.0f, std::min(Settings::worldWidth, Settings::worldHeight) * std::numbers::pi_v<float> };
        std::uniform_real_distribution<float> angle_dist_{ 0.0f, 2.0f * std::numbers::pi_v<float> };

        std::uniform_int_distribution<int> flare_count_dist_{ Settings::minFlareCount, Settings::maxFlareCount };

        std::normal_distribution<float> outer_rad_dist_{ Settings::meanStarOuterRadius, Settings::devStarOuterRadius };
        std::normal_distribution<float> inner_rad_ratio_dist_{ Settings::meanStarInnerRatio,  Settings::devStarInnerRatio };
        std::normal_distribution<float> normal_dist_{ 0.0f, 1.0f };

        std::vector<std::unique_ptr<entity::Star>> stars_;

        static constexpr bool distribute_circular_ = true;
    };
}