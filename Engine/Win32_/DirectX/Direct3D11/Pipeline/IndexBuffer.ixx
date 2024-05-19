module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module IndexBuffer;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
#else
import <vector>;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11::pipeline
{
    class IndexBuffer final : public Bindable
    {
    public:
        IndexBuffer(Graphics& gfx, const std::vector<unsigned short int>& indices);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    public:
        UINT GetCount() const noexcept;


    protected:
        Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer_;

        UINT count_;


    private:
    };
}