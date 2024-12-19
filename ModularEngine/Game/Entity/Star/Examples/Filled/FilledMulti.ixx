module;

#include <FatNamespaces.hpp>
#include <StarRealmNamespaces.hpp>

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledMulti final : public StarBase<style::type::Filled, style::effect::MultiColor>
    {
    public:
        explicit FilledMulti(FATSPACE_D3D11::Graphics<>& gfx, const Descriptor& desc, FATSPACE_UTIL::ViewXM& worldView);

        explicit FilledMulti() = delete;
        explicit FilledMulti(const FilledMulti& src) = delete;
        explicit FilledMulti(FilledMulti&& src) = delete;

        auto operator = (const FilledMulti& src) -> FilledMulti& = delete;
        auto operator = (FilledMulti&& src)      -> FilledMulti& = delete;
        virtual ~FilledMulti() noexcept final = default;


    protected:


    private:
    };
}