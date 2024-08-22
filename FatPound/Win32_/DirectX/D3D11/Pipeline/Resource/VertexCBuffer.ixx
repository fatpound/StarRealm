module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:VertexCBuffer;

import :CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class VertexCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit VertexCBuffer() = delete;
        explicit VertexCBuffer(const VertexCBuffer& src) = delete;
        explicit VertexCBuffer(VertexCBuffer&& src) = delete;

        VertexCBuffer& operator = (const VertexCBuffer& src) = delete;
        VertexCBuffer& operator = (VertexCBuffer&& src) = delete;
        virtual ~VertexCBuffer() noexcept final = default;


    public:
        auto operator <=> (const VertexCBuffer& rhs) const = delete;
        bool operator ==  (const VertexCBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final
        {
            pImmediateContext->VSSetConstantBuffers(0u, 1u, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}