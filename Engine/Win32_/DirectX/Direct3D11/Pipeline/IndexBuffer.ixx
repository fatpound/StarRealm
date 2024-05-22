module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module IndexBuffer;

import D3D11Graphics;
import Bindable;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
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