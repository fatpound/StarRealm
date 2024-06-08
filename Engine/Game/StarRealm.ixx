module;

#include "../Win32_/FatWin32_.hpp"

export module StarRealm;

import FatPound.Win32.Direct3D11;
import Camera;
import CameraController;
import FatPound.Util;
import Star;

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
        void DoFrame_();


    private:
        std::vector<std::unique_ptr<entity::Star>> stars_;
        
        NAMESPACE_D3D11::Window wnd_;
        NAMESPACE_D3D11::Graphics& gfx_;
        
        NAMESPACE_DIRECTX::Camera camera_;
        NAMESPACE_DIRECTX::CameraController camera_controller_;

        NAMESPACE_UTIL::AutoTimer timer_;
        
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