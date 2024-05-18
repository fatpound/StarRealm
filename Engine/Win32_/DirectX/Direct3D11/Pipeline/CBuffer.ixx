module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

export module CBuffer;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
#else
import <cstring>;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename C>
    class CBuffer : public Bindable
    {
    public:
        CBuffer(D3D11_NAMESPACE::Graphics& gfx, const C& consts)
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
        CBuffer(D3D11_NAMESPACE::Graphics& gfx)
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
        virtual void Update(D3D11_NAMESPACE::Graphics& gfx, const C& consts) final
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