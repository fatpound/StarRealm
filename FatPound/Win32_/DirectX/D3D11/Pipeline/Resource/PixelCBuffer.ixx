module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelCBuffer;

import :CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit PixelCBuffer() = delete;
        explicit PixelCBuffer(const PixelCBuffer& src) = delete;
        explicit PixelCBuffer(PixelCBuffer&& src) = delete;

        PixelCBuffer& operator = (const PixelCBuffer& src) = delete;
        PixelCBuffer& operator = (PixelCBuffer&& src) = delete;
        virtual ~PixelCBuffer() noexcept final = default;


    public:
        auto operator <=> (const PixelCBuffer& rhs) const = delete;
        bool operator ==  (const PixelCBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->PSSetConstantBuffers(0u, 1u, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}