module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelCBuffer;

import :CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename C>
    class PixelCBuffer final : public CBuffer<C>
    {
        using CBuffer<C>::CBuffer;

    public:
        explicit PixelCBuffer() = delete;
        explicit PixelCBuffer(const PixelCBuffer& src) = delete;
        explicit PixelCBuffer(PixelCBuffer&& src) = delete;

        PixelCBuffer& operator = (const PixelCBuffer& src) = delete;
        PixelCBuffer& operator = (PixelCBuffer&& src) = delete;
        virtual ~PixelCBuffer() noexcept = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->PSSetConstantBuffers(0u, 1u, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}