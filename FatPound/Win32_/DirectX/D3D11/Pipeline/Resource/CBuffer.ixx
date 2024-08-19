module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename C>
    class CBuffer : public Bindable
    {
    public:
        explicit CBuffer(Graphics<>& gfx, const C& consts)
        {
            D3D11_BUFFER_DESC cbd = {};
            cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbd.Usage = D3D11_USAGE_DYNAMIC;
            cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            cbd.MiscFlags = 0u;
            cbd.ByteWidth = sizeof(consts);
            cbd.StructureByteStride = 0u;

            D3D11_SUBRESOURCE_DATA csd = {};
            csd.pSysMem = &consts;

            Bindable::GetDevice_(gfx)->CreateBuffer(&cbd, &csd, &m_pConstantBuffer_);
        }
        explicit CBuffer(Graphics<>& gfx)
        {
            D3D11_BUFFER_DESC cbd = {};
            cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbd.Usage = D3D11_USAGE_DYNAMIC;
            cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            cbd.MiscFlags = 0u;
            cbd.ByteWidth = sizeof(C);
            cbd.StructureByteStride = 0u;

            Bindable::GetDevice_(gfx)->CreateBuffer(&cbd, nullptr, &m_pConstantBuffer_);
        }

        explicit CBuffer() = delete;
        explicit CBuffer(const CBuffer& src) = delete;
        explicit CBuffer(CBuffer&& src) = delete;

        CBuffer& operator = (const CBuffer& src) = delete;
        CBuffer& operator = (CBuffer&& src) = delete;
        virtual ~CBuffer() noexcept = default;


    public:
        virtual void Update(Graphics<>& gfx, const C& consts) final
        {
            D3D11_MAPPED_SUBRESOURCE msr;

            Bindable::GetContext_(gfx)->Map(
                m_pConstantBuffer_.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &msr
            );

            std::memcpy(msr.pData, &consts, sizeof(consts));

            Bindable::GetContext_(gfx)->Unmap(m_pConstantBuffer_.Get(), 0u);
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer_;


    private:
    };
}