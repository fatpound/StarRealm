module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.ColorBase;

import std;

namespace dx = DirectX;

export namespace fatpound::starrealm::entity::star
{
    template <std::size_t ColorCount>
    class ColorBase
    {
    public:
        struct CBuffer final
        {
            dx::XMFLOAT4 vertex_colors[ColorCount];
        };
        

    public:
        static auto GeneratePixelCBuffer() -> CBuffer
        {
            std::minstd_rand mrng(std::random_device{}());
            std::uniform_real_distribution<float> rgb_dist(0.0f, 1.0f);

            CBuffer cbuf = {};

            for (std::size_t i = 0u; i < ColorCount; ++i)
            {
                cbuf.vertex_colors[i] = dx::XMFLOAT4{
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    rgb_dist(mrng),
                    1.0f
                };
            }

            return cbuf;
        }


    protected:


    private:
    };
}