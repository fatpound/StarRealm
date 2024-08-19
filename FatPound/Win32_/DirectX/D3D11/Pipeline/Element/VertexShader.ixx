module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:VertexShader;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class VertexShader final : public Bindable
    {
    public:
        explicit VertexShader(Graphics<>& gfx, const std::wstring& path);

        explicit VertexShader() = delete;
        explicit VertexShader(const VertexShader& src) = delete;
        explicit VertexShader(VertexShader&& src) = delete;

        VertexShader& operator = (const VertexShader& src) = delete;
        VertexShader& operator = (VertexShader&& src) = delete;
        virtual ~VertexShader() noexcept final = default;


    public:
        virtual void Bind(Graphics<>& gfx) override final;


    public:
        auto GetBytecode() const noexcept -> ID3DBlob*;


    protected:
        ::Microsoft::WRL::ComPtr<ID3DBlob>           m_pBytecodeBlob_;
        ::Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader_;


    private:
    };
}