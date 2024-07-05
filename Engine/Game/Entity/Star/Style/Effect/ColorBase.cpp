module;

#include <DirectXMath.h>

module StarRealm.Entity.Star.Style.Effect.ColorBase;

namespace dx = DirectX;

namespace fatpound::starrealm::entity::star
{
    auto ColorBase::GeneratePixelCBuffer() -> CBuffer
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

    auto ColorBase::GeneratePixelSBuffer(std::size_t color_count) -> SBuffer
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
}