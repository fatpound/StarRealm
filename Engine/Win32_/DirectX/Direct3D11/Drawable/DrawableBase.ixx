module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

#include <cassert>

export module DrawableBase;

import Bindable;
import Drawable;
import IndexBuffer;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <cmath>;
import <cstdint>;
/**/
import <vector>;
import <memory>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    template <class C>
    class DrawableBase : public Drawable
    {
    public:


    protected:


    private:
    };
}