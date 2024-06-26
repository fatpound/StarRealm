module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.ColorBase;

import std;

namespace dx = DirectX;

export namespace fatpound::starrealm::entity::star
{
    class ColorBase
    {
    public:
        struct CBuffer final
        {
            using Type = dx::XMFLOAT4;

            dx::XMFLOAT4 vertex_color;
        };
        struct SBuffer final
        {
            using Type = CBuffer::Type;

            std::vector<Type> vertex_colors;
        };
        

    public:
        static auto GeneratePixelCBuffer() -> CBuffer
        {
            std::minstd_rand mrng(std::random_device{}());
            std::uniform_real_distribution<float> rgb_dist(0.0f, 1.0f);

            CBuffer cbuf =
            {
                {
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    1.0f
                }
            };

            return cbuf;
        }

        static auto GeneratePixelSBuffer(std::size_t color_count) -> SBuffer
        {
            std::minstd_rand mrng(std::random_device{}());
            std::uniform_real_distribution<float> rgb_dist(0.0f, 1.0f);

            SBuffer sbuf = {};

            sbuf.vertex_colors.reserve(color_count);

            for (std::size_t i = 0u; i < color_count; ++i)
            {
                sbuf.vertex_colors.emplace_back(
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    1.0f
                );
            }

            return sbuf;
        }


    protected:


    private:
    };
}