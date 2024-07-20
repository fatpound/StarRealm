module;

#include "../Win32_/FatWin32_Namespaces.hpp"

export module StarRealm.StarFactory;

export import StarRealm.Entity;

import FatPound.Win32.D3D11;

import std;

export namespace starrealm
{
    class StarFactory final
    {
    public:
        struct Settings final
        {
            static constexpr auto starCount_ = 150u;
            static constexpr auto minFlareCount_ = 2u;
            static constexpr auto maxFlareCount_ = 7u;

            static constexpr auto worldWidth_  = 15.0f;
            static constexpr auto worldHeight_ = 10.0f;

            static constexpr auto maxStarRadius_ = 1.5f;
            static constexpr auto minStarRadius_ = 0.4f;
            static constexpr auto minStarDepth_  = 0.2f;
            static constexpr auto maxStarDepth_  = 10.0f;

            static constexpr auto minRotationSpeed_ = -1.0f * std::numbers::pi_v<float>;
            static constexpr auto maxRotationSpeed_ =  1.0f * std::numbers::pi_v<float>;
        };


    public:
        StarFactory(NAMESPACE_D3D11::Graphics& gfx)
            :
            gfx_(gfx)
        {
            stars_.reserve(Settings::starCount_);

            while (stars_.size() < Settings::starCount_)
            {
                stars_.push_back(GenerateStar_());
            }
        }


    public:
        auto GetStars() && -> std::vector<std::unique_ptr<entity::Star>>&&;


    protected:


    private:
        auto GenerateStar_() -> std::unique_ptr<entity::Star>;


    private:
        NAMESPACE_D3D11::Graphics& gfx_;

        std::vector<std::unique_ptr<entity::Star>> stars_;

        std::minstd_rand rng_{ std::random_device{}() };

        std::uniform_real_distribution<float> outer_rad_dist_{ 0.4f, 0.8f };
        std::uniform_real_distribution<float> inner_rad_dist_{ 0.1f, 0.3f };
        std::uniform_real_distribution<float> x_dist_{ -Settings::worldWidth_,  Settings::worldWidth_ };
        std::uniform_real_distribution<float> y_dist_{ -Settings::worldHeight_, Settings::worldHeight_ };
        std::uniform_real_distribution<float> zed_depth_dist_{ Settings::minStarDepth_, Settings::maxStarDepth_ };
        std::uniform_real_distribution<float> rotation_speed_dist_{ Settings::minRotationSpeed_, Settings::maxRotationSpeed_ };

        std::uniform_int_distribution<int> flare_count_dist_{ Settings::minFlareCount_, Settings::maxFlareCount_ };
    };
}