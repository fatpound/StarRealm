module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelSBuffer;

import :SBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename S>
    class PixelSBuffer final : public SBuffer<S>
    {
        using SBuffer<S>::SBuffer;

    public:
        explicit PixelSBuffer() = delete;
        explicit PixelSBuffer(const PixelSBuffer& src) = delete;
        explicit PixelSBuffer(PixelSBuffer&& src) = delete;

        PixelSBuffer& operator = (const PixelSBuffer& src) = delete;
        PixelSBuffer& operator = (PixelSBuffer&& src) = delete;
        virtual ~PixelSBuffer() noexcept final = default;


    public:
        virtual void Bind(GfxDevicePack& gfx_devicePack) override final
        {
            gfx_devicePack.m_pImmediateContext->PSSetShaderResources(0u, 1u, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}