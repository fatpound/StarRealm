module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.StarStyle.Color:ColoringBase;

export import :Base;

import std;

export namespace starrealm::entity::star_style::color
{
    template <typename T>
    class ColoringBase : public Base<T>
    {
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
        explicit ColoringBase()                        = delete;
        explicit ColoringBase(const ColoringBase&)     = delete;
        explicit ColoringBase(ColoringBase&&) noexcept = delete;

        auto operator = (const ColoringBase&)     -> ColoringBase& = delete;
        auto operator = (ColoringBase&&) noexcept -> ColoringBase& = delete;
        ~ColoringBase() noexcept                                   = delete;


    public:
        static auto GeneratePixelCBuffer() -> CBuffer
        {
            std::minstd_rand mrng(std::random_device{}());
            std::uniform_real_distribution<float> rgb_dist(0.0f, 1.0f);

            const CBuffer cbuf =
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

        static auto GeneratePixelSBuffer(const std::size_t color_count) -> SBuffer
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
