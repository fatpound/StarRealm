module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module VertexBuffer;

import D3D11Graphics;
import Bindable;

#ifdef NDEBUG
import std.core;
#else
import <vector>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class VertexBuffer : public Bindable
    {
    public:
        template <class V>
        VertexBuffer(fatpound::dx11::D3DGraphics& gfx, const std::vector<V>& vertices)
            :
            stride_(sizeof(V))
        {
            D3D11_BUFFER_DESC bd = {};
            bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.CPUAccessFlags = 0u;
            bd.MiscFlags = 0u;
            bd.ByteWidth = static_cast<UINT>(sizeof(V) * vertices.size());
            bd.StructureByteStride = sizeof(V);

            D3D11_SUBRESOURCE_DATA sd = {};
            sd.pSysMem = vertices.data();

            GetDevice_(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer_);
        }


    public:
        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;

        UINT stride_;


    private:
    };
}