module;

#include <DirectXMath.h>

export module StarRealm.Entity.Star.Style.Effect.ColorBase;

import std;

export namespace fatpound::starrealm::entity::star
{
    class ColorBase
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
        static auto GeneratePixelCBuffer() -> CBuffer;

        static auto GeneratePixelSBuffer(std::size_t color_count) -> SBuffer;


    protected:


    private:
    };
}