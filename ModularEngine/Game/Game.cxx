module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#if IN_RELEASE

#define SCREEN_WIDTH    static_cast<UINT>(::GetSystemMetrics(SM_CXSCREEN))
#define SCREEN_HEIGHT   static_cast<UINT>(::GetSystemMetrics(SM_CYSCREEN))

#else

#define SCREEN_WIDTH    800u
#define SCREEN_HEIGHT   600u

#endif // IN_RELEASE

module StarRealm;

namespace dx = DirectX;

namespace starrealm
{
    Game::Game()
        :
        m_wnd_(std::make_shared<FATSPACE_WIN32::WndClassEx>(L"fat->pound WindowClassEx: " + std::to_wstring(s_game_id_++)), std::make_shared<FATSPACE_UTIL_IO::Keyboard>(), std::make_shared<FATSPACE_UTIL_IO::Mouse>(), L"StarRealm " + std::to_wstring(s_game_id_), FATSPACE_UTIL::ScreenSizeInfo{ SCREEN_WIDTH, SCREEN_HEIGHT }),
        m_gfx_(m_wnd_.GetHandle(), FATSPACE_UTIL::ScreenSizeInfo{ m_wnd_.GetClientWidth<UINT>(), m_wnd_.GetClientHeight<UINT>() }),
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

    auto Game::IsRunning() const -> bool
    {
        return not IsOver();
    }
    auto Game::IsOver() const -> bool
    {
        return m_wnd_.IsClosing();
    }

    void Game::Init_()
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

    void Game::Go_()
    {
        Init_();

        while (IsRunning())
        {
            m_gfx_.BeginFrame();
            DoFrame_();
            m_gfx_.EndFrame();
        }
    }
    void Game::DoFrame_()
    {
        const auto& deltaTime = m_timer_.Mark();

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
}