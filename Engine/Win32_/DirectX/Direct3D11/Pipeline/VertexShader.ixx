module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module Direct3D11.Pipeline.VertexShader;

import Direct3D11.Graphics;
import Direct3D11.Pipeline.Bindable;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11::pipeline
{
    class VertexShader final : public Bindable
    {
    public:
        VertexShader(Graphics& gfx, const std::wstring& path);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    public:
        ID3DBlob* GetBytecode() const noexcept;


    protected:
        Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob_;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader_;


    private:
    };
}