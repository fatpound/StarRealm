module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:VertexBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class VertexBuffer final : public Bindable
    {
    public:
        template <typename T>
        explicit VertexBuffer(ID3D11Device* pDevice, const std::vector<T>& vertices)
            :
            m_stride_(sizeof(T))
        {
            D3D11_BUFFER_DESC bd = {};
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.CPUAccessFlags = 0u;
            bd.MiscFlags = 0u;
            bd.ByteWidth = static_cast<UINT>(m_stride_ * vertices.size());
            bd.StructureByteStride = m_stride_;

            D3D11_SUBRESOURCE_DATA sd = {};
            sd.pSysMem = vertices.data();

            pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer_);
        }

        explicit VertexBuffer() = delete;
        explicit VertexBuffer(const VertexBuffer& src) = delete;
        explicit VertexBuffer(VertexBuffer&& src) = delete;

        VertexBuffer& operator = (const VertexBuffer& src) = delete;
        VertexBuffer& operator = (VertexBuffer&& src) = delete;
        virtual ~VertexBuffer() noexcept final = default;


    public:
        auto operator <=> (const VertexBuffer& rhs) const = delete;
        bool operator ==  (const VertexBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer_;

        UINT m_stride_;


    private:
    };
}