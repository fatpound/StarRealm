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
        Star& operator = (const Star& src) = delete;

        Star(Star&& src) = delete;
        Star& operator = (Star&& src) = delete;
        virtual ~Star() noexcept = default;


    public:
        static auto Make(const DirectX::XMFLOAT2& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;
        static auto MakeWithCentre(const DirectX::XMFLOAT2& radius, const DirectX::XMFLOAT3& centre, std::size_t flare_count = 4u) -> std::vector<DirectX::XMFLOAT3>;


    public:
        virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX override final;

        virtual void Update(float delta_time) noexcept override final;

        virtual auto GetPosition() const noexcept -> DirectX::XMFLOAT3 final;

        virtual float GetOuterRadius() const noexcept final;


    public:
        bool IsWithinArea(const DirectX::XMFLOAT3& position, const DirectX::XMFLOAT2& radius);


    protected:
        DirectX::XMFLOAT2 radius_; // outer_radius, inner_radius

        DirectX::XMFLOAT3 position_;

        float rotation_speed_;
        float roll_;


    private:
    };
}