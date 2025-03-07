module;

#include <FatNamespaces.hpp>

export module StarRealm;

export import :StarFactory;

export import StarRealm.View;

import FatPound;

import std;

export namespace starrealm
{
    class Game final
    {
        using Settings = StarFactory<>::Settings;

    public:
        explicit Game();
        explicit Game(const Game&)     = delete;
        explicit Game(Game&&) noexcept = delete;

        auto operator = (const Game& src)     -> Game& = delete;
        auto operator = (Game&& src) noexcept -> Game& = delete;
        ~Game() noexcept                               = default;


    public:
        auto IsRunning() const -> bool;
        auto IsOver()    const -> bool;


    protected:
        

    private:
        void Init_();
        void Go_();
        void DoFrame_();


    private:
        inline static std::size_t s_game_id_{};


    private:
        FATSPACE_WIN32::WindowEx m_wnd_;
        FATSPACE_D3D11::Graphics<> m_gfx_;
        
        view::Camera m_camera_;

        FATSPACE_UTIL::ViewXM m_viewXM_;
        FATSPACE_UTIL::Timer m_timer_;
        
        std::vector<std::unique_ptr<entity::Star>> m_stars_;

        std::jthread m_game_loop_;
    };
}

module : private;