module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module IndexBuffer;

import D3D11Graphics;
import Bindable;

#ifdef NDEBUG
import std.core;
#else
import <vector>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class IndexBuffer : public Bindable
    {
    public:
        IndexBuffer(fatpound::dx11::D3DGraphics& gfx, const std::vector<unsigned short int>& indices);


    public:
        UINT GetCount() const noexcept;

        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;

        UINT count_;


    private:
    };
}