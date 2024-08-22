module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelSBuffer;

import :SBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelSBuffer final : public SBuffer<T>
    {
        using SBuffer<T>::SBuffer;

    public:
        explicit PixelSBuffer() = delete;
        explicit PixelSBuffer(const PixelSBuffer& src) = delete;
        explicit PixelSBuffer(PixelSBuffer&& src) = delete;

        PixelSBuffer& operator = (const PixelSBuffer& src) = delete;
        PixelSBuffer& operator = (PixelSBuffer&& src) = delete;
        virtual ~PixelSBuffer() noexcept final = default;


    public:
        auto operator <=> (const PixelSBuffer& rhs) const = delete;
        bool operator ==  (const PixelSBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->PSSetShaderResources(0u, 1u, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}