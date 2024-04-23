module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Star;

import DrawableBase;

#ifdef NDEBUG
import std.core;
#else
import <cmath>;
import <cstdint>;
/**/
import <vector>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class Star : public DrawableBase<Star>
    {
    public:
        struct Descriptor final
        {
            const DirectX::XMFLOAT2& radius;
            const DirectX::XMFLOAT3& position;

            const std::size_t flare_count;

            const float rotation_speed;
        };


    public:
        Star(const Descriptor& desc);

        Star() = default;
        Star(const Star& src) = delete;
        Star(Star&& src) = delete;
        Star& operator = (const Star& src) = delete;
        Star& operator = (Star&& src) = delete;
        virtual ~Star() = default;


    public:
        static std::vector<DirectX::XMFLOAT3> Make(const float outer_radius, const float inner_radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u, bool add_centre = true)
        {
            std::vector<DirectX::XMFLOAT3> star;
            const std::size_t capacity = flare_count * 2u;
        
            star.reserve(capacity + 1u);
        
            const float dTheta = 2.0f * DirectX::XM_PI / static_cast<float>(capacity);
        
            for (std::size_t i = 0u; i < capacity; ++i)
            {
                const float rad = (i % 2u == 0u)
                    ? outer_radius
                    : inner_radius
                    ;
                
                star.emplace_back(
                    rad * std::cos(static_cast<float>(i) * dTheta) + centre.x,
                    rad * std::sin(static_cast<float>(i) * dTheta) + centre.y,
                    centre.z
                );
            }

            if (add_centre)
            {
                star.emplace_back(centre.x, centre.y, centre.z);
            }
        
            return star;
        }

        DirectX::XMMATRIX GetTransformXM() const noexcept override;

        DirectX::XMFLOAT3 GetPosition() const noexcept;

        float GetOuterRadius() const noexcept;

        void Update(float delta_time) noexcept override;


    protected:
        DirectX::XMFLOAT2 radius_; // outer_radius, inner_radius

        DirectX::XMFLOAT3 position_;

        float rotation_speed_;
        float roll_;


    private:
    };
}