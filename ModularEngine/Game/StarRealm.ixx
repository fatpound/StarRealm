module;

#include "../Win32_/FatWin32_.hpp"

export module StarRealm;

import :StarFactory;

import FatPound;

import std;

export namespace starrealm
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
        ~Game() noexcept = default;


    public:
        int Go();


    protected:
        

    private:
        void DoFrame_();


    private:
        NAMESPACE_WIN32::Window wnd_;

        NAMESPACE_D3D11::Graphics gfx_;
        
        NAMESPACE_UTIL::Camera camera_;
        NAMESPACE_UTIL::AutoTimer timer_;
        
        std::vector<std::unique_ptr<entity::Star>> stars_;
    };
}