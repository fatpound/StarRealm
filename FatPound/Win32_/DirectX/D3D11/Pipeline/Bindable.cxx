module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Bindable;

namespace fatpound::win32::d3d11::pipeline
{
    auto Bindable::GetDevice_(Graphics& gfx) noexcept -> ID3D11Device*
    {
        return gfx.m_gfxres_.m_pDevice.Get();
    }

    auto Bindable::GetContext_(Graphics& gfx) noexcept -> ID3D11DeviceContext*
    {
        return gfx.m_gfxres_.m_pImmediateContext.Get();
    }
}