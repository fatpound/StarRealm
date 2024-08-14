module;

#include <FatBuildSettings.hpp>

#include <FatWin32_.hpp>

#include <DirectXMath.h>

#if IN_RELEASE
#define SCREEN_WIDTH    static_cast<UINT>(GetSystemMetrics(SM_CXSCREEN))
#define SCREEN_HEIGHT   static_cast<UINT>(GetSystemMetrics(SM_CYSCREEN))
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
        m_wnd_(L"StarRealm", NAMESPACE_WIN32::Window::ClientSizeInfo{ SCREEN_WIDTH, SCREEN_HEIGHT }),
        m_gfx_(m_wnd_.GetHwnd(), NAMESPACE_D3D11::Graphics::SizeInfo{ m_wnd_.GetClientWidth<UINT>(), m_wnd_.GetClientHeight<UINT>() }),
        m_camera_(Settings::s_minStarDepth, Settings::s_maxStarDepth),
        m_camera_controller_(m_camera_, m_wnd_.GetMouse(), m_wnd_.GetKeyboard()),
        m_stars_{ StarFactory{ m_gfx_ }.GetStars() }
    {
        m_gfx_.SetProjectionXM(
            ::dx::XMMatrixPerspectiveLH(
                1.0f,
                m_wnd_.GetClientHeight<float>() / m_wnd_.GetClientWidth<float>(), // 1 / Aspect Ratio
                Settings::s_minStarDepth,
                Settings::s_maxStarDepth * 2.0f
            )
        );
    }

    int Game::Go()
    {
        std::optional<WPARAM> error_code;

        while (true)
        {
            error_code = NAMESPACE_WIN32::Window::ProcessMessages();

            if (error_code) [[unlikely]]
            {
                return static_cast<int>(*error_code);
            }

            if (m_wnd_.GetKeyboard().KeyIsPressed(VK_ESCAPE)) [[unlikely]]
            {
                m_wnd_.Kill();

                return 0;
            }

            m_gfx_.BeginFrame();
            DoFrame_();
            m_gfx_.EndFrame();
        }
    }

    void Game::DoFrame_()
    {
        m_camera_controller_.Update();

        const auto& delta_time = m_timer_.Mark();
        
        m_gfx_.SetCameraXM(m_camera_.GetMatrix());

        for (auto& star : m_stars_)
        {
            if (not m_wnd_.GetKeyboard().KeyIsPressed(VK_SPACE)) [[likely]]
            {
                star->Update(delta_time);
            }

            star->Draw(m_gfx_);
        }
    }
}