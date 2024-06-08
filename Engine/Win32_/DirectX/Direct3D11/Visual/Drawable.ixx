module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Drawable;

import Direct3D11.Graphics;
import Direct3D11.Pipeline.Bindable;
import Direct3D11.Pipeline.IndexBuffer;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
import std.memory;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

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
        virtual ~Drawable() = default;


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