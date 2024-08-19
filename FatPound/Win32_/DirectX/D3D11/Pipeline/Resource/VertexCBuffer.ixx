module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:VertexCBuffer;

import :CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename C>
    class VertexCBuffer final : public CBuffer<C>
    {
        using CBuffer<C>::CBuffer;

    public:
        explicit VertexCBuffer() = delete;
        explicit VertexCBuffer(const VertexCBuffer& src) = delete;
        explicit VertexCBuffer(VertexCBuffer&& src) = delete;

        VertexCBuffer& operator = (const VertexCBuffer& src) = delete;
        VertexCBuffer& operator = (VertexCBuffer&& src) = delete;
        virtual ~VertexCBuffer() noexcept final = default;


    public:
        virtual void Bind(GfxDevicePack& gfx_devicePack) override final
        {
            gfx_devicePack.m_pImmediateContext->VSSetConstantBuffers(0u, 1u, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}