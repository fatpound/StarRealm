module;

#include <FatWin32_Settings.hpp>
#include <FatWin32_Namespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Viewport;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
    void Viewport::SetDefault(const GraphicsResourcePack& gfxResPack, const NAMESPACE_UTIL::ScreenSizeInfo gfxDimensions)
    {
        D3D11_VIEWPORT vp = {};
        vp.Width  = static_cast<FLOAT>(gfxDimensions.m_width);
        vp.Height = static_cast<FLOAT>(gfxDimensions.m_height);
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0.0f;
        vp.TopLeftY = 0.0f;

        gfxResPack.m_pImmediateContext->RSSetViewports(1u, &vp);
    }
}