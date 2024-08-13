module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.FilledMulti;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style.Type.Filled;
import StarRealm.Entity.Star.Style.Effect.MultiColor;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledMulti final : public StarBase<style::type::Filled, style::effect::MultiColor>
    {
    public:
        explicit FilledMulti(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        explicit FilledMulti() = delete;
        explicit FilledMulti(const FilledMulti& src) = delete;
        explicit FilledMulti(FilledMulti&& src) = delete;

        FilledMulti& operator = (const FilledMulti& src) = delete;
        FilledMulti& operator = (FilledMulti&& src) = delete;
        virtual ~FilledMulti() = default;


    protected:


    private:
    };
}