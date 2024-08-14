module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.FilledSingle;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledSingle final : public StarBase<style::type::Filled, style::effect::SingleColor>
    {
    public:
        explicit FilledSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        explicit FilledSingle() = delete;
        explicit FilledSingle(const FilledSingle& src) = delete;
        explicit FilledSingle(FilledSingle&& src) = delete;

        FilledSingle& operator = (const FilledSingle& src) = delete;
        FilledSingle& operator = (FilledSingle&& src) = delete;
        virtual ~FilledSingle() = default;


    protected:


    private:
    };
}