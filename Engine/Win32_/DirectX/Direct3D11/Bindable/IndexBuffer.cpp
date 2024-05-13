module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

module IndexBuffer;

namespace fatpound::win32::d3d11
{
    IndexBuffer::IndexBuffer(Graphics& gfx, const std::vector<unsigned short int>& indices)
        :
        count_(static_cast<UINT>(indices.size()))
    {
        D3D11_BUFFER_DESC bd = {};
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.CPUAccessFlags = 0u;
        bd.MiscFlags = 0u;
        bd.ByteWidth = count_ * sizeof(unsigned short int);
        bd.StructureByteStride = sizeof(unsigned short int);

        D3D11_SUBRESOURCE_DATA sd = {};
        sd.pSysMem = indices.data();

        Bindable::GetDevice_(gfx)->CreateBuffer(&bd, &sd, &pIndexBuffer_);
    }

    UINT IndexBuffer::GetCount() const noexcept
    {
        return count_;
    }

    void IndexBuffer::Bind(Graphics& gfx) noexcept
    {
        Bindable::GetContext_(gfx)->IASetIndexBuffer(pIndexBuffer_.Get(), DXGI_FORMAT_R16_UINT, 0u);
    }
}