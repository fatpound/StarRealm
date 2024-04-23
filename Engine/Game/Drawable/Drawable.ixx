module;

#include "../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module Drawable;

import D3D11Graphics;
import Bindable;
import IndexBuffer;

#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <vector>;
import <memory>;
//
import <typeinfo>;
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class Drawable
    {
    public:
        Drawable() = default;
        Drawable(const Drawable& src) = delete;
        Drawable(Drawable&& src) = delete;
        Drawable& operator = (const Drawable& src) = delete;
        Drawable& operator = (Drawable&& src) = delete;
        ~Drawable() = default;


    public:
        virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;

        virtual void Update(float delta_time) noexcept = 0;
        void Draw(fatpound::dx11::D3DGraphics& gfx) const noexcept(!IS_DEBUG);


    protected:
        void AddBind_(std::unique_ptr<Bindable> bind) noexcept(!IS_DEBUG);
        void AddIndexBuffer_(std::unique_ptr<IndexBuffer> ibuf) noexcept;


    protected:
        const IndexBuffer* pCIndexBuffer_ = nullptr;


    private:
        virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds_() const noexcept = 0;


    private:
        std::vector<std::unique_ptr<Bindable>> binds_;
    };
}