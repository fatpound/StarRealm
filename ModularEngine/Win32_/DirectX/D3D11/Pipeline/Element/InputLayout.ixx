module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element:InputLayout;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Graphics;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class InputLayout final : public Bindable
    {
    public:
        explicit InputLayout(Graphics& gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* pVertexShaderBytecode);

        explicit InputLayout() = delete;
        explicit InputLayout(const InputLayout& src) = delete;
        explicit InputLayout(InputLayout&& src) = delete;

        InputLayout& operator = (const InputLayout& src) = delete;
        InputLayout& operator = (InputLayout&& src) = delete;
        virtual ~InputLayout() noexcept = default;


    public:
        virtual void Bind(Graphics& gfx) noexcept override final;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout_;


    private:
    };
}