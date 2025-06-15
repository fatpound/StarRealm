module;

#include <_macros/Namespaces.hxx>

module StarRealm.Entity.Star.Style.Color:ColoringBase;

import <DirectXMath.h>;
import :Base;

import FatPound;

import std;

namespace dx = DirectX;

namespace starrealm::entity::star_style::color
{
    template <typename T>
    class ColoringBase : public Base<T>
    {
    public:
        struct CBuffer final
        {
            using Type = dx::XMFLOAT4;

            Type vertex_color;
        };
        struct SBuffer final
        {
            using Type = CBuffer::Type;

            std::vector<Type> vertex_colors;
        };


    public:
        explicit ColoringBase()                        = delete;
        explicit ColoringBase(const ColoringBase&)     = delete;
        explicit ColoringBase(ColoringBase&&) noexcept = delete;

        auto operator = (const ColoringBase&)     -> ColoringBase& = delete;
        auto operator = (ColoringBase&&) noexcept -> ColoringBase& = delete;
        ~ColoringBase() noexcept                                   = delete;


    public:
        static auto GeneratePixelCBuffer() -> CBuffer
        {
            std::minstd_rand rng(std::random_device{}());
            std::uniform_real_distribution<float> dist(0.0F, 1.0F);

            return CBuffer
            {
                {
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    1.0F
                }
            };
        }

        static auto GeneratePixelSBuffer(const std::size_t& colorCount) -> SBuffer
        {
            SBuffer sbuf{};
            sbuf.vertex_colors.reserve(colorCount);

            std::minstd_rand rng(std::random_device{}());
            std::uniform_real_distribution<float> dist(0.0F, 1.0F);
            
            for (std::size_t i{}; i < colorCount; ++i)
            {
                sbuf.vertex_colors.emplace_back(
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    FATSPACE_RANDOM::RandNumber<>(rng, dist),
                    1.0F
                );
            }

            return sbuf;
        }


    protected:


    private:
    };
}
