module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.FilledBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledBlend final : public StarBase<style::type::Filled, style::effect::Blend>
    {
    public:
        explicit FilledBlend(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView);

        explicit FilledBlend()                       = delete;
        explicit FilledBlend(const FilledBlend&)     = delete;
        explicit FilledBlend(FilledBlend&&) noexcept = delete;

        auto operator = (const FilledBlend&)     -> FilledBlend& = delete;
        auto operator = (FilledBlend&&) noexcept -> FilledBlend& = delete;
        virtual ~FilledBlend() noexcept final                    = default;


    protected:


    private:
    };
}

module : private;