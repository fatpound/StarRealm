module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Effect:Color.Base;

import :Base;

import std;

export namespace starrealm::entity::star::style::effect
{
    template <class C>
    class ColorBase_ : public Base_<C>
    {
    public:
        explicit ColorBase_() = delete;
        explicit ColorBase_(const ColorBase_& src) = delete;
        explicit ColorBase_(ColorBase_&& src) = delete;

        ColorBase_& operator = (const ColorBase_& src) = delete;
        ColorBase_& operator = (ColorBase_&& src) = delete;
        ~ColorBase_() noexcept = delete;


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