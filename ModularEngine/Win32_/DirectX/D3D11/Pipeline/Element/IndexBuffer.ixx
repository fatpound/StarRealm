module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:IndexBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class IndexBuffer final : public Bindable
    {
    public:
        IndexBuffer(Graphics& gfx, const std::vector<unsigned short int>& indices);

        IndexBuffer() = delete;
        IndexBuffer(const IndexBuffer& src) = delete;
        IndexBuffer(IndexBuffer&& src) = delete;

        IndexBuffer& operator = (const IndexBuffer& src) = delete;
        IndexBuffer& operator = (IndexBuffer&& src) = delete;
        virtual ~IndexBuffer() noexcept = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    public:
        auto GetCount() const noexcept -> UINT;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer_;

        UINT m_count_;


    private:
    };
}