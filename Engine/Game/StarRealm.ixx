module;

#include "../Win32_/FatWin32_.hpp"

export module StarRealm;

import D3D11Window;
import D3D11Graphics;
import Camera;
import CameraController;
import FatTimer;
import Star;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
import std.memory;
#else
import <cstdint>;
import <vector>;
import <optional>;
import <numbers>;
import <memory>;
//
import <random>;
import <ranges>;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

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
        void DoFrame_();


    private:
        std::vector<std::unique_ptr<Star>> stars_;
        
        fatpound::win32::d3d11::Window wnd_;
        fatpound::win32::d3d11::Graphics& gfx_;
        
        fatpound::win32::d3d11::Camera camera_;
        fatpound::win32::d3d11::CameraController camera_controller_;

        fatpound::util::Timer timer_;
        
        static constexpr std::size_t star_count_ = 150u;
        static constexpr std::size_t minFlareCount_ = 2u;
        static constexpr std::size_t maxFlareCount_ = 7u;

        static constexpr float worldWidth_  = 15.0f;
        static constexpr float worldHeight_ = 10.0f;

        static constexpr float maxStarRadius_ = 1.5f;
        static constexpr float minStarRadius_ = 0.4f;
        static constexpr float minStarDepth_  = 0.2f;
        static constexpr float maxStarDepth_  = 10.0f;

        static constexpr float minRotationSpeed_ = -1.0f * std::numbers::pi_v<float>;
        static constexpr float maxRotationSpeed_ =  1.0f * std::numbers::pi_v<float>;
    };
}