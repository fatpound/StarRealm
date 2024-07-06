module;

#include "../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#if IN_RELEASE
#define SCREEN_WIDTH    GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT   GetSystemMetrics(SM_CYSCREEN)
#else
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600
#endif // IN_RELEASE

module StarRealm;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    Game::Game()
        :
        wnd_(L"StarRealm",   NAMESPACE_WIN32::Window::ClientSizeInfo{ SCREEN_WIDTH, SCREEN_HEIGHT }),
        gfx_(wnd_.GetHwnd(), NAMESPACE_D3D11::Graphics::SizeInfo{ wnd_.GetClientWidth<int>(), wnd_.GetClientHeight<int>() }), // they are the same as SCREEN_ MACROS
        camera_(Settings::minStarDepth_, Settings::maxStarDepth_),
        camera_controller_(camera_, wnd_.mouse, wnd_.kbd),
        stars_{ StarFactory{gfx_}.GetStars() }
    {
        gfx_.SetProjection(
            dx::XMMatrixPerspectiveLH(
                1.0f,
                wnd_.GetClientHeight<float>() / wnd_.GetClientWidth<float>(), // 1 / Aspect Ratio
                Settings::minStarDepth_,
                Settings::maxStarDepth_ * 2.0f
            )
        );
    }

    Game::~Game() noexcept
    {

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
        const auto& delta_time = timer_.Mark();

        camera_controller_.Update(delta_time);
        
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