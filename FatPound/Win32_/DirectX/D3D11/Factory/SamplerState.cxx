module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:SamplerState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void SamplerState::Create(
        const GfxResource& gfxres,
        ::wrl::ComPtr<ID3D11SamplerState>& pSamplerState,
        D3D11_SAMPLER_DESC desc
    )
    {
        HRESULT hr;

        hr = gfxres.m_device_pack.m_pDevice->CreateSamplerState(&desc, &pSamplerState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create SamplerState");
        }
    }
}