module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.Element:IndexBuffer;

namespace fatpound::win32::d3d11::pipeline::element
{
    IndexBuffer::IndexBuffer(ID3D11Device* pDevice, const std::vector<unsigned short int>& indices)
        :
        m_count_(static_cast<UINT>(indices.size()))
    {
        D3D11_BUFFER_DESC bd = {};
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.CPUAccessFlags = 0u;
        bd.MiscFlags = 0u;
        bd.ByteWidth = m_count_ * sizeof(unsigned short int);
        bd.StructureByteStride = sizeof(unsigned short int);

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = indices.data();

        pDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer_);
    }

    auto IndexBuffer::GetCount() const noexcept -> UINT
    {
        return m_count_;
    }

    void IndexBuffer::Bind(ID3D11DeviceContext* pImmediateContext)
    {
        pImmediateContext->IASetIndexBuffer(m_pIndexBuffer_.Get(), DXGI_FORMAT_R16_UINT, 0u);
    }
}