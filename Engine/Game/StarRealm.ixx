module;

#include "../Win32_/FatWin32_.hpp"

export module StarRealm;

import FatPound.Win32;
import FatPound.Util;

import StarRealm.Entity;

import std;

export namespace fatpound::starrealm
{
    class Game final
    {
    public:
        Game();
        Game(const Game& src) = delete;
        Game& operator = (const Game& src) = delete;

        Game(Game&& src) = delete;
        Game& operator = (Game&& src) = delete;
        ~Game() noexcept;


    public:
        int Go();


    protected:
        

    private:
        struct Settings final
        {
            static constexpr auto star_count_    = 150u;
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


    private:
        void DoFrame_();


    private:
        NAMESPACE_D3D11::Window wnd_;
        NAMESPACE_D3D11::Graphics& gfx_;
        
        NAMESPACE_UTIL::Camera camera_;
        NAMESPACE_UTIL::CameraController camera_controller_;
        NAMESPACE_UTIL::AutoTimer timer_;
        
        std::vector<std::unique_ptr<entity::Star>> stars_;
    };
}