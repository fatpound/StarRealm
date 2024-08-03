module;

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
        wnd_(L"StarRealm", NAMESPACE_WIN32::Window::ClientSizeInfo{ SCREEN_WIDTH, SCREEN_HEIGHT }),
        gfx_(wnd_.GetHwnd(), NAMESPACE_D3D11::Graphics::SizeInfo{ wnd_.GetClientWidth<UINT>(), wnd_.GetClientHeight<UINT>() }),
        camera_(Settings::s_minStarDepth, Settings::s_maxStarDepth),
        camera_controller_(camera_, wnd_.mouse, wnd_.kbd),
        stars_{ StarFactory{ gfx_ }.GetStars() }
    {
        gfx_.SetProjection(
            dx::XMMatrixPerspectiveLH(
                1.0f,
                wnd_.GetClientHeight<float>() / wnd_.GetClientWidth<float>(), // 1 / Aspect Ratio
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

            if (wnd_.kbd.KeyIsPressed(VK_ESCAPE)) [[unlikely]]
            {
                wnd_.Kill();

                return 0;
            }

            gfx_.BeginFrame();
            DoFrame_();
            gfx_.EndFrame();
        }
    }

    void Game::DoFrame_()
    {
        camera_controller_.Update();

        const auto& delta_time = timer_.Mark();
        
        gfx_.SetCamera(camera_.GetMatrix());

        for (auto& star : stars_)
        {
            if (not wnd_.kbd.KeyIsPressed(VK_SPACE)) [[likely]]
            {
                star->Update(delta_time);
            }

            star->Draw(gfx_);
        }
    }
}