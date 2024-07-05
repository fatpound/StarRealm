module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module FatPound.Win32.D3D11.Visual.Drawable;

import FatPound.Win32.D3D11.Graphics;
import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::win32::d3d11::visual
{
    class Drawable
    {
    public:
        Drawable() = default;
        Drawable(const Drawable& src) = delete;
        Drawable& operator = (const Drawable& src) = delete;

        Drawable(Drawable&& src) = delete;
        Drawable& operator = (Drawable&& src) = delete;
        virtual ~Drawable() noexcept = default;


    public:
        virtual auto GetTransformXM() const noexcept -> DirectX::XMMATRIX = 0;

        virtual void Update(float delta_time) noexcept = 0;

        virtual void Draw(Graphics& gfx) const noexcept(IN_RELEASE) final;

        
    protected:
        virtual void AddBind_(std::unique_ptr<NAMESPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE) final;
        virtual void AddIndexBuffer_(std::unique_ptr<NAMESPACE_PIPELINE::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final;


    protected:
        const NAMESPACE_PIPELINE::IndexBuffer* pCIndexBuffer_ = nullptr;


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>>& = 0;


    private:
        std::vector<std::unique_ptr<NAMESPACE_PIPELINE::Bindable>> binds_;
    };
}