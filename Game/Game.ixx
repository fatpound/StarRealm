module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

export module StarRealm;

export import :StarFactory;

export import StarRealm.View;

import FatPound;

import std;

namespace dx = DirectX;

#if IN_RELEASE
#define ScreenWidth  static_cast<UINT>(::GetSystemMetrics(SM_CXSCREEN))
#define ScreenHeight static_cast<UINT>(::GetSystemMetrics(SM_CYSCREEN))
#else
static constexpr UINT ScreenWidth  = 800u;
static constexpr UINT ScreenHeight = 600u;
#endif

export namespace starrealm
{
    class Game final
    {
        using Settings = StarFactory<>::Settings;

    public:
        explicit Game()
            :
            m_wnd_(std::make_shared<FATSPACE_WIN32::WndClassEx>(L"fat->pound WindowClassEx: " + std::to_wstring(s_game_id_++)), L"StarRealm " + std::to_wstring(s_game_id_), FATSPACE_UTIL_GFX::SizePack{ ScreenWidth, ScreenHeight }),
            m_gfx_(m_wnd_.GetHandle(), FATSPACE_UTIL_GFX::SizePack{ m_wnd_.GetClientWidth<UINT>(), m_wnd_.GetClientHeight<UINT>() }),
            m_camera_(Settings{}.m_maxStarDepth, m_wnd_.m_pKeyboard, m_wnd_.m_pMouse),
            ////////////////////////////////
#pragma region (gameloop w/o C4355)
#pragma warning (push)
#pragma warning (disable : 4355)
            m_game_loop_{ &Game::Go_, this }
#pragma warning (pop)
#pragma endregion
            ////////////////////////////////
        {

        }
        explicit Game(const Game&)     = delete;
        explicit Game(Game&&) noexcept = delete;

        auto operator = (const Game&)     -> Game& = delete;
        auto operator = (Game&&) noexcept -> Game& = delete;
        ~Game() noexcept                           = default;


    public:
        auto IsRunning() const -> bool
        {
            return not IsOver();
        }
        auto IsOver()    const -> bool
        {
            return m_wnd_.IsClosing();
        }


    protected:
        

    private:
        void Init_()
        {
            Settings default_settings;

            m_viewXM_.SetProjectionXM(
                ::dx::XMMatrixPerspectiveLH(
                    1.0f,
                    m_wnd_.GetClientHeight<float>() / m_wnd_.GetClientWidth<float>(), // 1 / Aspect Ratio
                    default_settings.m_minStarDepth,
                    default_settings.m_maxStarDepth * 20.0f
                )
            );

            m_stars_ = StarFactory<>{ m_gfx_, m_viewXM_ }.GetStars();
        }
        void Go_()
        {
            Init_();

            m_timer_.Start();

            while (IsRunning())
            {
                m_gfx_.BeginFrame<false, 0.0f, 0.0f, 0.25f>();
                DoFrame_();
                m_gfx_.EndFrame<>();
            }
        }
        void DoFrame_()
        {
            m_timer_.Stop();
            const auto& deltaTime = m_timer_.GetElapsed_s();
            m_timer_.Start();

            m_camera_.Update();

            m_viewXM_.SetCameraXM(m_camera_.GetMatrix());

            auto* const pImmediateContext = m_gfx_.GetImmediateContext();

            if (not m_wnd_.m_pKeyboard->KeyIsPressed(VK_SPACE))
            {
                for (auto& star : m_stars_)
                {
                    star->Update(deltaTime);
                    star->Draw(pImmediateContext);
                }
            }
            else
            {
                for (auto& star : m_stars_)
                {
                    star->Draw(pImmediateContext);
                }
            }
        }


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
