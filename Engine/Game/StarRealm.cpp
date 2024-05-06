module;

#include "../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

#if _MSVC_LANG == 202002L
#ifndef NDEBUG
#include <algorithm>
#endif // !NDEBUG
#endif // _MSVC_LANG == 202002L

#ifdef NDEBUG
#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#else
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#endif // NDEBUG

module StarRealm;

import StarHollowSingle;
import StarHollowMulti;
import StarHollowBlend;
import StarFilledSingle;
import StarFilledMulti;
import StarFilledBlend;

namespace dx = DirectX;

namespace fatpound::starrealm
{
    Game::Game()
        try
        :
        wnd_(L"StarRealm", SCREEN_WIDTH, SCREEN_HEIGHT),
        gfx_(wnd_.Gfx()),
        camera_(minStarDepth_, maxStarDepth_),
        camera_controller_(wnd_.mouse, wnd_.kbd, camera_)
    {
        class Factory final
        {
        public:
            Factory(fatpound::win32::d3d11::Graphics& gfx, const Game& game)
                :
                gfx_(gfx),
                game_(game)
            {

            }

        public:
            std::unique_ptr<Star> operator () ()
            {
                dx::XMFLOAT2 radius;
                dx::XMFLOAT3 position;

                // Non-Colliding Star Generation Loop
                while (true)
                {
                    radius = dx::XMFLOAT2(outer_rad_dist_(mrng_), inner_rad_dist_(mrng_));
                    // position = dx::XMFLOAT3(x_dist_(mrng_), y_dist_(mrng_), 1.0f);
                    position = dx::XMFLOAT3(x_dist_(mrng_), y_dist_(mrng_), zed_depth_dist_(mrng_));

                    const auto& collide = [&](const std::unique_ptr<Star>& star) -> bool
                        {
                            const dx::XMFLOAT3& existing_star_pos = star->GetPosition();

                            const dx::XMVECTOR& position_vec = dx::XMLoadFloat3(&position);
                            const dx::XMVECTOR& existing_star_pos_vec = dx::XMLoadFloat3(&existing_star_pos);
                            const dx::XMVECTOR& difference = dx::XMVectorSubtract(existing_star_pos_vec, position_vec);

                            const float& length = dx::XMVectorGetX(dx::XMVector3Length(difference));

                            return length < (radius.x + star->GetOuterRadius());
                        };

                    if (std::ranges::none_of(game_.stars_, collide))
                    {
                        break;
                    }
                }

                const Star::Descriptor desc{
                    radius,
                    position,
                    static_cast<std::size_t>(flare_count_dist_(mrng_)),
                    rotation_speed_dist_(mrng_)
                };
                
                switch (mrng_() % 6u)
                {
                case 0:
                    return std::make_unique<StarHollowSingle>(gfx_, desc);
                
                case 1:
                    return std::make_unique<StarHollowMulti>(gfx_, desc);
                
                case 2:
                    return std::make_unique<StarHollowBlend>(gfx_, desc);
                
                case 3:
                    return std::make_unique<StarFilledSingle>(gfx_, desc);
                
                case 4:
                    return std::make_unique<StarFilledMulti>(gfx_, desc);
                
                case 5:
                    return std::make_unique<StarFilledBlend>(gfx_, desc);
                
                default:
                    return nullptr;
                }
            }

        protected:

        private:
            std::minstd_rand mrng_{ std::random_device{}() };

            std::uniform_real_distribution<float> outer_rad_dist_{ 0.4f, 0.8f };
            std::uniform_real_distribution<float> inner_rad_dist_{ 0.1f, 0.3f };
            std::uniform_real_distribution<float> x_dist_{ -worldWidth_, worldWidth_ };
            std::uniform_real_distribution<float> y_dist_{ -worldHeight_, worldHeight_ };
            std::uniform_real_distribution<float> zed_depth_dist_{ minStarDepth_, maxStarDepth_ };
            std::uniform_real_distribution<float> rotation_speed_dist_{ minRotationSpeed_, maxRotationSpeed_ };

            std::uniform_int_distribution<int> flare_count_dist_{ minFlareCount_, maxFlareCount_ };

            fatpound::win32::d3d11::Graphics& gfx_;
            const Game& game_;
        };
        
        stars_.reserve(star_count_);

        std::generate_n(std::back_inserter(stars_), star_count_, Factory{gfx_, *this});

        gfx_.SetProjection(
            dx::XMMatrixPerspectiveLH(
                1.0f,
                wnd_.GetHeight<float>() / wnd_.GetWidth<float>(), // 1 / Aspect Ratio
                minStarDepth_,
                maxStarDepth_ * 2.0f
            )
        );
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
    catch (...)
    {
        MessageBox(nullptr, L"Non-STD Exception was thrown when entering StarRealm CTOR!", L"Game Error", MB_OK | MB_ICONERROR);

        throw;
    }

    Game::~Game() noexcept
    {

    }

    int Game::Go()
    {
        std::optional<WPARAM> error_code;

        while (true)
        {
            error_code = fatpound::win32::d3d11::Window::ProcessMessages();

            if (error_code) [[unlikely]]
            {
                return static_cast<int>(*error_code);
            }

            if (wnd_.kbd.KeyIsPressed(VK_ESCAPE)) [[unlikely]]
            {
                wnd_.Kill();

                return 0;
            }

            gfx_.BeginFrame(0.0f, 0.0f, 0.25f);
            DoFrame_();
            gfx_.EndFrame();
        }
    }

    void Game::DoFrame_()
    {
        auto delta_time = timer_.Mark();

        camera_controller_.Update(delta_time);
        
        gfx_.SetCamera(camera_.GetMatrix());

        for (auto& star : stars_) // MSVC SSA Optimizer's "Loop if-unswitching" will optimize this loop
        {
            if (wnd_.kbd.KeyIsPressed(VK_SPACE)) [[unlikely]]
            {
                star->Update(0.0f);
            }
            else [[likely]]
            {
                star->Update(delta_time);
            }

            star->Draw(gfx_);
        }
    }
}