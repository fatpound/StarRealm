module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.Direct3D11.Pipeline.SBuffer;

import FatPound.Win32.Direct3D11.Pipeline.Bindable;
import FatPound.Win32.Direct3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename S>
    class SBuffer : public Bindable
    {
    public:
        SBuffer(Graphics& gfx, const std::vector<S>& structures)
        {
            D3D11_BUFFER_DESC sbd = {};
            sbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            sbd.Usage = D3D11_USAGE_DEFAULT;
            sbd.CPUAccessFlags = 0u;
            sbd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            sbd.ByteWidth = sizeof(S) * static_cast<UINT>(structures.size());
            sbd.StructureByteStride = sizeof(S);

            D3D11_SUBRESOURCE_DATA initData = {};
            initData.pSysMem = structures.data();

            Bindable::GetDevice_(gfx)->CreateBuffer(&sbd, &initData, &pConstantBuffer_);

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.Format = DXGI_FORMAT_UNKNOWN;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            srvDesc.Buffer.ElementWidth = static_cast<UINT>(structures.size());

            Bindable::GetDevice_(gfx)->CreateShaderResourceView(pConstantBuffer_.Get(), &srvDesc, &pShaderResourceView_);
            Bindable::GetContext_(gfx)->VSSetShaderResources(0u, 1u, pShaderResourceView_.GetAddressOf());
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView_ = nullptr;
        Microsoft::WRL::ComPtr<ID3D11Buffer>             pConstantBuffer_     = nullptr;


    private:
    };
}