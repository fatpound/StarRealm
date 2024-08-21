module;

export module FatPound.Util.Color;

import std;

export namespace fatpound
{
    namespace util
    {
        class Color final
        {
        public:
            explicit constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 0xFFui8)
            {
                dword = (static_cast<std::uint32_t>(alpha) << 24)
                    | (static_cast<std::uint32_t>(r) << 16)
                    | (static_cast<std::uint32_t>(g) << 8)
                    | (static_cast<std::uint32_t>(b));
            }
            explicit constexpr Color(int r, int g, int b)
                :
                Color(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b))
            {

            }
            explicit constexpr Color(std::uint32_t dw)
                :
                dword(dw | 0xFF'00'00'00u)
            {

            }
            explicit constexpr Color(Color col, unsigned char alpha)
                :
                Color((static_cast<std::uint32_t>(alpha) << 24) | col.dword)
            {

            }

            explicit constexpr Color() = default;
            constexpr Color(const Color& src) noexcept
                :
                dword(src.dword)
            {

            }
            constexpr Color(Color&& src) noexcept = default;

            constexpr Color& operator = (const Color& src) noexcept
            {
                dword = src.dword;

                return *this;
            }
            constexpr Color& operator = (Color&& src) noexcept = default;
            constexpr ~Color() noexcept = default;


        public:
            bool operator == (const Color src) const
            {
                return dword == src.dword;
            }


        public:
            void SetAlpha(unsigned char x)
            {
                dword = (dword & 0x00'FF'FF'FFu) | (std::uint32_t(x) << 24);
            }
            void SetR(unsigned char r)
            {
                dword = (dword & 0xFF'00'FF'FFu) | (std::uint32_t(r) << 16);
            }
            void SetG(unsigned char g)
            {
                dword = (dword & 0xFF'FF'00'FFu) | (std::uint32_t(g) << 8);
            }
            void SetB(unsigned char b)
            {
                dword = (dword & 0xFF'FF'FF'00u) | std::uint32_t(b);
            }

            constexpr unsigned char GetAlpha() const
            {
                return dword >> 24;
            }
            constexpr unsigned char GetR()     const
            {
                return (dword >> 16u) & 0xFFu;
            }
            constexpr unsigned char GetG()     const
            {
                return (dword >> 8u) & 0xFFu;
            }
            constexpr unsigned char GetB()     const
            {
                return dword & 0xFFu;
            }


        public:
            std::uint32_t dword = 0xFF'FF'FF'FFu;


        protected:


        private:
        };
    }

    namespace colors
    {
        constexpr auto MakeRGB(unsigned char r, unsigned char g, unsigned char b) -> util::Color
        {
            return util::Color{
                (static_cast<std::uint32_t>(r) << 16) |
                (static_cast<std::uint32_t>(g) << 8) |
                static_cast<std::uint32_t>(b)
            };
        }

        constexpr auto Black     = MakeRGB(  0u,   0u,   0u);
        constexpr auto Gray      = MakeRGB(128u, 128u, 128u);
        constexpr auto LightGray = MakeRGB(192u, 192u, 192u);
        constexpr auto White     = MakeRGB(255u, 255u, 255u);

        constexpr auto Red       = MakeRGB(255u,   0u,   0u);
        constexpr auto Green     = MakeRGB(  0u, 255u,   0u);
        constexpr auto Blue      = MakeRGB(  0u,   0u, 255u);
        constexpr auto Yellow    = MakeRGB(255u, 255u,   0u);
        constexpr auto Cyan      = MakeRGB(  0u, 255u, 255u);
        constexpr auto Magenta   = MakeRGB(255u,   0u, 255u);
    }
}