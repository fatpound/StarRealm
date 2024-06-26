module;

#include "../Win32_/FatWin32_.hpp"

export module StarRealm;

import FatPound.Win32;
import FatPound.Util;

import StarRealm.StarFactory;

import std;

export namespace fatpound::starrealm
{
    class Game final
    {
        using Settings = StarFactory::Settings;

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
        NAMESPACE_D3D11::Window wnd_;
        NAMESPACE_D3D11::Graphics& gfx_;
        
        NAMESPACE_UTIL::Camera camera_;
        NAMESPACE_UTIL::CameraController camera_controller_;
        NAMESPACE_UTIL::AutoTimer timer_;
        
        std::vector<std::unique_ptr<entity::Star>> stars_;
    };
}