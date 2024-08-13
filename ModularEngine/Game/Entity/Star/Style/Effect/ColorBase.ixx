module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Effect.ColorBase;

import StarRealm.Entity.Star.Style.EffectBase;

import std;

export namespace starrealm::entity::star
{
    template <class C>
    class ColorBase : public StyleEffect_<C>
    {
    public:
        explicit ColorBase() = delete;
        explicit ColorBase(const ColorBase& src) = delete;
        explicit ColorBase(ColorBase&& src) = delete;

        ColorBase& operator = (const ColorBase& src) = delete;
        ColorBase& operator = (ColorBase&& src) = delete;
        ~ColorBase() noexcept = delete;


    public:
        struct CBuffer final
        {
            using Type = ::DirectX::XMFLOAT4;

            Type vertex_color;
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