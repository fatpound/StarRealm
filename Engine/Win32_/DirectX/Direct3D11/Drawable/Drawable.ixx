module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Drawable;

import D3D11Graphics;
import Bindable;
import IndexBuffer;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <vector>;
import <memory>;
//
import <typeinfo>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
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
        virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;

        virtual void Update(float delta_time) noexcept = 0;
        virtual void Draw(Graphics& gfx) const noexcept(IN_RELEASE) final;


    protected:
        virtual void AddBind_(std::unique_ptr<Bindable> bind) noexcept(IN_RELEASE) final;
        virtual void AddIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) noexcept(IN_RELEASE) final;


    protected:
        const IndexBuffer* pCIndexBuffer_ = nullptr;


    private:
        virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds_() const noexcept(IN_RELEASE) = 0;


    private:
        std::vector<std::unique_ptr<Bindable>> binds_;
    };
}