module;

#include <FatNamespaces.hxx>

export module StarRealm.Entity.Star;

import <DirectXMath.h>;

import FatPound;

import std;

namespace dx = DirectX;

export namespace starrealm::entity
{
    class Star : public fatpound::win32::d3d11::visual::Drawable
    {
    public:
        struct RadiusPack final
        {
            float outer_radius;
            float inner_radius;
        };
        struct Descriptor final
        {
            dx::XMFLOAT3 position;

            RadiusPack radiuses;

            std::size_t flare_count;

            float rotation_speed;
        };


    public:
        explicit Star(const Descriptor& desc) noexcept
            :
            m_position_(desc.position),
            m_radiuses_(desc.radiuses),
            m_rotation_speed_(desc.rotation_speed),
            m_roll_(0.0F)
        {

        }

        explicit Star()                = default;
        explicit Star(const Star&)     = delete;
        explicit Star(Star&&) noexcept = delete;

        auto operator = (const Star&)     -> Star& = delete;
        auto operator = (Star&&) noexcept -> Star& = delete;
        virtual ~Star() noexcept override          = default;


    public:
        auto operator <=> (const Star& rhs) const noexcept
        {
            return m_radiuses_.outer_radius <=> rhs.m_radiuses_.outer_radius;
        }


    public:
        template <bool WithCentre = false>
        static auto Make(
            const RadiusPack& radiuses,
            const dx::XMFLOAT3& centre,
            const std::size_t& flare_count = 4U) -> std::vector<dx::XMFLOAT3>
        {
            const auto& capacity = flare_count * 2U;

            std::vector<dx::XMFLOAT3> star;
            star.reserve(capacity + 1U);

            const auto& dTheta = 2.0F * dx::XM_PI / static_cast<float>(capacity);

            for (std::size_t i{}; i < capacity; ++i)
            {
                const auto& rad = (i % 2U == 0U)
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
        virtual auto GetTransformXM() const noexcept -> dx::XMMATRIX override final
        {
            const auto& pos_vec = dx::XMLoadFloat3(&m_position_);

            return
                dx::XMMatrixTranslationFromVector(dx::XMVectorNegate(pos_vec)) *
                dx::XMMatrixRotationZ(m_roll_) *
                dx::XMMatrixTranslationFromVector(pos_vec);
        }

        virtual auto GetPosition() const noexcept -> dx::XMFLOAT3 final
        {
            return m_position_;
        }

        virtual auto GetOuterRadius() const noexcept -> float final
        {
            return m_radiuses_.outer_radius;
        }

        virtual void Update(const float delta_time) noexcept override final
        {
            m_roll_ += (delta_time * m_rotation_speed_);
        }


    public:
        auto IsWithinArea(const dx::XMFLOAT3& position, const float radius) const noexcept -> bool
        {
            const auto& distance = FATSPACE_GEOMETRY::Distance(this->m_position_, position);
            const auto& radsum   = m_radiuses_.outer_radius + radius;

            return radsum > distance;
        }


    protected:
        dx::XMFLOAT3 m_position_;

        RadiusPack m_radiuses_;

        float m_rotation_speed_;
        float m_roll_;


    private:
    };
}
