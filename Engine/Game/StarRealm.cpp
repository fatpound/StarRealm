module;

#include "../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <algorithm>

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
        wnd_(L"StarRealm", NAMESPACE_D3D11::Window::ClientSizeInfo{ SCREEN_WIDTH, SCREEN_HEIGHT }),
        gfx_(wnd_.Gfx()),
        camera_(Settings::minStarDepth_, Settings::maxStarDepth_),
        camera_controller_(camera_, wnd_.mouse, wnd_.kbd)
    {
        class Factory final
        {
        public:
            Factory(NAMESPACE_D3D11::Graphics& gfx, const Game& game)
                :
                gfx_(gfx),
                game_(game)
            {

            }

        public:
            auto operator () () -> std::unique_ptr<entity::Star>
            {
                dx::XMFLOAT2 radius;
                dx::XMFLOAT3 position;

                while (true)
                {
                    radius = dx::XMFLOAT2(outer_rad_dist_(mrng_), inner_rad_dist_(mrng_));
                    position = dx::XMFLOAT3(x_dist_(mrng_), y_dist_(mrng_), zed_depth_dist_(mrng_));

                    const auto& collide = [&](const auto& star) -> bool
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

                const entity::Star::Descriptor desc{
                    radius,
                    position,
                    static_cast<std::size_t>(flare_count_dist_(mrng_)),
                    rotation_speed_dist_(mrng_)
                };
                
                switch (mrng_() % 6u)
                {
                case 0:
                    return std::make_unique<entity::star::HollowSingle>(gfx_, desc);
                
                case 1:
                    return std::make_unique<entity::star::HollowMulti>(gfx_, desc);
                
                case 2:
                    return std::make_unique<entity::star::HollowBlend>(gfx_, desc);
                
                case 3:
                    return std::make_unique<entity::star::FilledSingle>(gfx_, desc);
                
                case 4:
                    return std::make_unique<entity::star::FilledMulti>(gfx_, desc);
                
                case 5:
                    return std::make_unique<entity::star::FilledBlend>(gfx_, desc);
                
                default:
                    return nullptr;
                }
            }

        protected:

        private:
            std::minstd_rand mrng_{ std::random_device{}() };

            std::uniform_real_distribution<float> outer_rad_dist_{ 0.4f, 0.8f };
            std::uniform_real_distribution<float> inner_rad_dist_{ 0.1f, 0.3f };
            std::uniform_real_distribution<float> x_dist_{ -Settings::worldWidth_,  Settings::worldWidth_ };
            std::uniform_real_distribution<float> y_dist_{ -Settings::worldHeight_, Settings::worldHeight_ };
            std::uniform_real_distribution<float> zed_depth_dist_{ Settings::minStarDepth_, Settings::maxStarDepth_ };
            std::uniform_real_distribution<float> rotation_speed_dist_{ Settings::minRotationSpeed_, Settings::maxRotationSpeed_ };

            std::uniform_int_distribution<int> flare_count_dist_{ Settings::minFlareCount_, Settings::maxFlareCount_ };

            NAMESPACE_D3D11::Graphics& gfx_;
            const Game& game_;
        };
        
        stars_.reserve(Settings::star_count_);

        std::generate_n(std::back_inserter(stars_), Settings::star_count_, Factory{gfx_, *this});

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
            error_code = NAMESPACE_D3D11::Window::ProcessMessages();

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