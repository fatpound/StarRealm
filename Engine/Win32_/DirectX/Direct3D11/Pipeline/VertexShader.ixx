module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline:VertexShader;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline
{
    class VertexShader final : public Bindable
    {
    public:
        VertexShader(Graphics& gfx, const std::wstring& path);


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    public:
        auto GetBytecode() const noexcept -> ID3DBlob*;


    protected:
        Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob_;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader_;


    private:
    };
}