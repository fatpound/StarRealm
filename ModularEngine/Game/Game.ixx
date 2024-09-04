module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm;

import :StarFactory;

import FatPound;

import std;

export namespace starrealm
{
    class Game final
    {
        using Settings = StarFactory<>::Settings;

    public:
        explicit Game();
        explicit Game(const Game& src) = delete;
        explicit Game(Game&& src) = delete;

        Game& operator = (const Game& src) = delete;
        Game& operator = (Game&& src) = delete;
        ~Game() noexcept = default;


    public:
        int Go();


    protected:
        

    private:
        void DoFrame_();


    private:
        Settings m_settings_;

        NAMESPACE_WIN32::Window m_wnd_;

        NAMESPACE_D3D11::Graphics<> m_gfx_;
        
        NAMESPACE_UTIL::Camera m_camera_;

        NAMESPACE_UTIL::AutoTimer m_timer_;
        
        std::vector<std::unique_ptr<entity::Star>> m_stars_;
    };
}