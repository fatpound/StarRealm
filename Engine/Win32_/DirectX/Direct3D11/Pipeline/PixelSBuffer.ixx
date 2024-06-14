module;

#include "../../../FatWin32_.hpp"

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.Direct3D11.Pipeline.PixelSBuffer;

import FatPound.Win32.Direct3D11.Pipeline.SBuffer;
import FatPound.Win32.Direct3D11.Pipeline.Bindable;
import FatPound.Win32.Direct3D11.Graphics;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename S>
    class PixelSBuffer final : public SBuffer<S>
    {
        using SBuffer<S>::SBuffer;

    public:
        virtual void Bind(Graphics& gfx) noexcept override final
        {
            Bindable::GetContext_(gfx)->PSSetShaderResources(0u, 1u, this->pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}