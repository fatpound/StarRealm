module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.Direct3D11.Pipeline.IndexBuffer;

import FatPound.Win32.Direct3D11.Pipeline.Bindable;
import FatPound.Win32.Direct3D11.Graphics;

import std;

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