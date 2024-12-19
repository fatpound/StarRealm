module;

#include <FatNamespaces.hpp>

#include <DirectXMath.h>

export module StarRealm.Entity.Star;

import FatPound;

import std;

export namespace starrealm::entity
{
    class Star : public FATSPACE_VISUAL::Drawable
    {
    public:
        struct RadiusPack final
        {
            float outer_radius;
            float inner_radius;
        };
        struct Descriptor final
        {
            ::DirectX::XMFLOAT3 position;

            RadiusPack radiuses;

            std::size_t flare_count;

            float rotation_speed;
        };


    public:
        explicit Star(const Descriptor& desc) noexcept;

        explicit Star() = default;
        explicit Star(const Star& src) = delete;
        explicit Star(Star&& src) = delete;

        auto operator = (const Star& src) -> Star& = delete;
        auto operator = (Star&& src)      -> Star& = delete;
        virtual ~Star() noexcept = default;


    public:
        auto operator <=> (const Star& rhs) const noexcept;


    public:
        template <bool WithCentre = false>
        static auto Make(
            const RadiusPack& radiuses,
            const ::DirectX::XMFLOAT3& centre,
            const std::size_t flare_count = 4u) -> std::vector<::DirectX::XMFLOAT3>
        {
            std::vector<::DirectX::XMFLOAT3> star;
            const std::size_t capacity = flare_count * 2u;

            star.reserve(capacity + 1u);

            const float dTheta = 2.0f * ::DirectX::XM_PI / static_cast<float>(capacity);

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
        virtual auto GetTransformXM() const noexcept -> ::DirectX::XMMATRIX override final;

        virtual auto GetPosition() const noexcept -> ::DirectX::XMFLOAT3 final;

        virtual auto GetOuterRadius() const noexcept -> float final;

        virtual void Update(const float delta_time) noexcept override final;


    public:
        auto IsWithinArea(const ::DirectX::XMFLOAT3& position, const float radius) const noexcept -> bool;


    protected:
        ::DirectX::XMFLOAT3 m_position_;

        RadiusPack m_radiuses_;

        float m_rotation_speed_;
        float m_roll_;


    private:
    };
}