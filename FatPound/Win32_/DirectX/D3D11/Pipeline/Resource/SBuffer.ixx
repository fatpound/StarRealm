module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:SBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class SBuffer : public Bindable
    {
    public:
        explicit SBuffer(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext, const std::vector<T>& structures)
        {
            D3D11_BUFFER_DESC sbd = {};
            sbd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            sbd.Usage = D3D11_USAGE_DEFAULT;
            sbd.CPUAccessFlags = 0u;
            sbd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
            sbd.ByteWidth = sizeof(T) * static_cast<UINT>(structures.size());
            sbd.StructureByteStride = sizeof(T);

            D3D11_SUBRESOURCE_DATA initData = {};
            initData.pSysMem = structures.data();

            pDevice->CreateBuffer(&sbd, &initData, &m_pStructuredBuffer_);

            D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
            srvDesc.Format = DXGI_FORMAT_UNKNOWN;
            srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
            srvDesc.Buffer.ElementWidth = static_cast<UINT>(structures.size());

            pDevice->CreateShaderResourceView(m_pStructuredBuffer_.Get(), &srvDesc, &m_pShaderResourceView_);
            pImmediateContext->VSSetShaderResources(0u, 1u, m_pShaderResourceView_.GetAddressOf());
        }

        explicit SBuffer() = delete;
        explicit SBuffer(const SBuffer& src) = delete;
        explicit SBuffer(SBuffer&& src) = delete;

        SBuffer& operator = (const SBuffer& src) = delete;
        SBuffer& operator = (SBuffer&& src) = delete;
        virtual ~SBuffer() noexcept = default;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pShaderResourceView_ = nullptr;
        ::Microsoft::WRL::ComPtr<ID3D11Buffer>             m_pStructuredBuffer_   = nullptr;


    private:
    };
}