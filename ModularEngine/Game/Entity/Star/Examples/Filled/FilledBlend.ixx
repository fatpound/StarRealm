module;

#include <FatWin32_Namespaces.hpp>

export module StarRealm.Entity.Star.FilledBlend;

import StarRealm.Entity.StarBase;
import StarRealm.Entity.Star.Style;

import FatPound;

export namespace starrealm::entity::star
{
    class FilledBlend final : public StarBase<style::type::Filled, style::effect::Blend>
    {
    public:
        explicit FilledBlend(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);

        explicit FilledBlend() = delete;
        explicit FilledBlend(const FilledBlend& src) = delete;
        explicit FilledBlend(FilledBlend&& src) = delete;

        FilledBlend& operator = (const FilledBlend& src) = delete;
        FilledBlend& operator = (FilledBlend&& src) = delete;
        virtual ~FilledBlend() = default;


    protected:


    private:
    };
}