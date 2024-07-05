module;

#include "../../../../FatWin32_.hpp"

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
        CBuffer(Graphics& gfx, const C& consts)
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

            Bindable::GetDevice_(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer_);
        }
        CBuffer(Graphics& gfx)
        {
            D3D11_BUFFER_DESC cbd = {};
            cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            cbd.Usage = D3D11_USAGE_DYNAMIC;
            cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
            cbd.MiscFlags = 0u;
            cbd.ByteWidth = sizeof(C);
            cbd.StructureByteStride = 0u;

            Bindable::GetDevice_(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer_);
        }


    public:
        virtual void Update(Graphics& gfx, const C& consts) final
        {
            D3D11_MAPPED_SUBRESOURCE msr;

            Bindable::GetContext_(gfx)->Map(
                pConstantBuffer_.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &msr
            );

            std::memcpy(msr.pData, &consts, sizeof(consts));

            Bindable::GetContext_(gfx)->Unmap(pConstantBuffer_.Get(), 0u);
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer_;


    private:
    };
}