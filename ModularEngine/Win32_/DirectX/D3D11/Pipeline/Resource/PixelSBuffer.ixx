module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelSBuffer;

import :SBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename S>
    class PixelSBuffer final : public SBuffer<S>
    {
        using SBuffer<S>::SBuffer;

    public:
        PixelSBuffer() = delete;
        PixelSBuffer(const PixelSBuffer& src) = delete;
        PixelSBuffer(PixelSBuffer&& src) = delete;

        PixelSBuffer& operator = (const PixelSBuffer& src) = delete;
        PixelSBuffer& operator = (PixelSBuffer&& src) = delete;
        virtual ~PixelSBuffer() noexcept = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->PSSetShaderResources(0u, 1u, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}