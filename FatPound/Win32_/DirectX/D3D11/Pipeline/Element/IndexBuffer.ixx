module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:IndexBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class IndexBuffer final : public Bindable
    {
    public:
        explicit IndexBuffer(ID3D11Device* pDevice, const std::vector<unsigned short int>& indices);

        explicit IndexBuffer() = delete;
        explicit IndexBuffer(const IndexBuffer& src) = delete;
        explicit IndexBuffer(IndexBuffer&& src) = delete;

        IndexBuffer& operator = (const IndexBuffer& src) = delete;
        IndexBuffer& operator = (IndexBuffer&& src) = delete;
        virtual ~IndexBuffer() noexcept final = default;


    public:
        auto operator <=> (const IndexBuffer& rhs) const = delete;
        bool operator ==  (const IndexBuffer& rhs) const = delete;


    public:
        virtual void Bind(ID3D11DeviceContext* pImmediateContext) override final;


    public:
        auto GetCount() const noexcept -> UINT;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer_;

        UINT m_count_;


    private:
    };
}