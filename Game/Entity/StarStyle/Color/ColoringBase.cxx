module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

module StarRealm.Entity.Star.Style.Color:ColoringBase;

import :Base;

import FatPound;

import std;

namespace starrealm::entity::star_style::color
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

            ::std::vector<Type> vertex_colors;
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
            return CBuffer
            {
                {
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    1.0F
                }
            };
        }

        static auto GeneratePixelSBuffer(const ::std::size_t& colorCount) -> SBuffer
        {
            SBuffer sbuf{};
            sbuf.vertex_colors.reserve(colorCount);

            for (::std::size_t i{}; i < colorCount; ++i)
            {
                sbuf.vertex_colors.emplace_back(
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    FATSPACE_RANDOM::RandFloat<>(0.0F, 1.0F),
                    1.0F
                );
            }

            return sbuf;
        }


    protected:


    private:
    };
}
