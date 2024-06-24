module;

#include "../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module StarRealm.Entity.Star;

import FatPound.Win32;

import std;

export namespace fatpound::starrealm::entity
{
    class Star : public NAMESPACE_VISUAL::DrawableBase<Star>
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
        static auto Make(const RadiusPack& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;
        static auto MakeWithCentre(const RadiusPack& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;


    public:
        virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override final;

        virtual void Update(float delta_time) noexcept override final;

        virtual auto GetPosition() const noexcept -> DirectX::XMFLOAT3 final;

        virtual float GetOuterRadius() const noexcept final;


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