module;

#include "../../FatWin32_.hpp"

#include <d3d11.h>
#include <wrl.h>

export module VertexShader;

import D3D11Graphics;
import Bindable;

#ifdef NDEBUG
import std.core;
#else
import <string>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class VertexShader : public Bindable
    {
    public:
        VertexShader(fatpound::dx11::D3DGraphics& gfx, const std::wstring& path);


    public:
        ID3DBlob* GetBytecode() const noexcept;

        void Bind(fatpound::dx11::D3DGraphics& gfx) noexcept override;


    protected:
        Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob_;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader_;


    private:
    };
}