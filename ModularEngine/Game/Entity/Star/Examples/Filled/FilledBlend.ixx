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

        explicit FilledBlend() = delete;
        explicit FilledBlend(const FilledBlend& src) = delete;
        explicit FilledBlend(FilledBlend&& src) = delete;

        auto operator = (const FilledBlend& src) -> FilledBlend& = delete;
        auto operator = (FilledBlend&& src)      -> FilledBlend& = delete;
        virtual ~FilledBlend() noexcept final = default;


    protected:


    private:
    };
}