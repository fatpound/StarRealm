module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:PixelShader;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class PixelShader final : public Bindable
    {
    public:
        explicit PixelShader(Graphics& gfx, const std::wstring& path);

        explicit PixelShader() = delete;
        explicit PixelShader(const PixelShader& src) = delete;
        explicit PixelShader(PixelShader&& src) = delete;

        PixelShader& operator = (const PixelShader& src) = delete;
        PixelShader& operator = (PixelShader&& src) = delete;
        virtual ~PixelShader() noexcept = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader_;


    private:
    };
}