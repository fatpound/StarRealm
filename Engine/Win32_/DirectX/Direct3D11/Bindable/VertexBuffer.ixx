module;

#include "../../../FatWin32_.hpp"

#include <wrl.h>

export module VertexBuffer;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
#else
import <vector>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    class VertexBuffer final : public Bindable
    {
    public:
        template <class V>
        VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
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

            Bindable::GetDevice_(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer_);
        }


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer_;

        UINT stride_;


    private:
    };
}