module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module StarRealm.Entity.Star;

import FatPound.Win32;

import std;

export namespace fatpound::starrealm::entity
{
    class Star : public NAMESPACE_VISUAL::Drawable
    {
    public:
        struct RadiusPack final
        {
            float outer_radius;
            float inner_radius;
        };
        struct Descriptor final
        {
            const DirectX::XMFLOAT3& position;

            const RadiusPack& radiuses;

            const std::size_t flare_count;

            const float rotation_speed;
        };


    public:
        Star(const Descriptor& desc);

        Star() = default;
        Star(const Star& src) = delete;
        Star& operator = (const Star& src) = delete;

        Star(Star&& src) = delete;
        Star& operator = (Star&& src) = delete;
        virtual ~Star() noexcept = default;


    public:
        template <bool WithCentre = false>
        static auto Make(const RadiusPack& radiuses, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>
        {
            std::vector<DirectX::XMFLOAT3> star;
            const std::size_t capacity = flare_count * 2u;

            star.reserve(capacity + 1u);

            const float dTheta = 2.0f * DirectX::XM_PI / static_cast<float>(capacity);

            for (std::size_t i = 0u; i < capacity; ++i)
            {
                const float rad = (i % 2u == 0u)
                    ? radiuses.outer_radius
                    : radiuses.inner_radius
                    ;

                star.emplace_back(
                    rad * std::cos(static_cast<float>(i) * dTheta) + centre.x,
                    rad * std::sin(static_cast<float>(i) * dTheta) + centre.y,
                    centre.z
                );
            }

            if constexpr (WithCentre)
            {
                star.emplace_back(centre.x, centre.y, centre.z);
            }

            return star;
        }


    public:
        virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override final;

        virtual auto GetPosition() const noexcept -> DirectX::XMFLOAT3 final;

        virtual float GetOuterRadius() const noexcept final;

        virtual void Update(float delta_time) noexcept override final;


    public:
        bool IsWithinArea(const DirectX::XMFLOAT3& position, const float& radius) const noexcept;


    protected:
        DirectX::XMFLOAT3 position_;

        RadiusPack radiuses_;

        float rotation_speed_;
        float roll_;


    private:
    };
}