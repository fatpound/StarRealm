module;

#include "../Win32_/FatWin32_Namespaces.hpp"

export module StarRealm.StarFactory;

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
            static constexpr auto starCount_ = 200u;
            static constexpr auto minFlareCount_ = 2u;
            static constexpr auto maxFlareCount_ = 7u;

            static constexpr auto worldWidth_  = 16.0f;
            static constexpr auto worldHeight_ =  9.0f;

            static constexpr auto meanStarOuterRadius_ = 0.6f;
            static constexpr auto devStarOuterRadius_  = 0.7f;
            static constexpr auto minStarOuterRadius_  = 0.5f;
            static constexpr auto maxStarOuterRadius_  = 1.0f;

            static constexpr auto meanStarInnerRatio_ = 0.4f;
            static constexpr auto devStarInnerRatio_  = 0.25f;
            static constexpr auto minStarInnerRatio_  = 0.2f;
            static constexpr auto maxStarInnerRatio_  = 0.5f;

            static constexpr auto minStarDepth_ = 0.4f;
            static constexpr auto maxStarDepth_ = 10.0f;

            static constexpr auto minRotationSpeed_ = -1.0f * std::numbers::pi_v<float>;
            static constexpr auto maxRotationSpeed_ =  1.0f * std::numbers::pi_v<float>;
        };


    public:
        StarFactory(NAMESPACE_D3D11::Graphics& gfx);


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

        std::uniform_real_distribution<float> x_dist_{ -Settings::worldWidth_,   Settings::worldWidth_ };
        std::uniform_real_distribution<float> y_dist_{ -Settings::worldHeight_,  Settings::worldHeight_ };
        std::uniform_real_distribution<float> z_dist_{  Settings::minStarDepth_, Settings::maxStarDepth_ };

        std::uniform_real_distribution<float> rotation_speed_dist_{ Settings::minRotationSpeed_, Settings::maxRotationSpeed_ };
        std::uniform_real_distribution<float> world_radius_dist_{ 0.0f, std::min(Settings::worldWidth_, Settings::worldHeight_) * 2.0f };
        std::uniform_real_distribution<float> angle_dist_{ 0.0f, 2.0f * std::numbers::pi_v<float> };

        std::uniform_int_distribution<int> flare_count_dist_{ Settings::minFlareCount_, Settings::maxFlareCount_ };

        std::normal_distribution<float> outer_rad_dist_{ Settings::meanStarOuterRadius_, Settings::devStarOuterRadius_ };
        std::normal_distribution<float> inner_rad_ratio_dist_{ Settings::meanStarInnerRatio_,  Settings::devStarInnerRatio_ };
        std::normal_distribution<float> normal_dist_{ 0.0f, 1.0f };

        std::vector<std::unique_ptr<entity::Star>> stars_;

        static constexpr bool distribute_circular_ = true;
    };
}