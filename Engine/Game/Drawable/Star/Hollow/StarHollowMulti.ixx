module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

export module StarHollowMulti;

import D3D11Graphics;
import StarBase;

#if (_MSVC_LANG > 202002L)
import std;
#else
#if (_MSVC_LANG == 202002L)
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <vector>;
import <memory>;
//
import <random>;
import <algorithm>;
import <numeric>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // (_MSVC_LANG == 202002L)
#endif // (_MSVC_LANG > 202002L)

export namespace fatpound::starrealm
{
    class StarHollowMulti final : public StarBase<StarHollowMulti>
    {
    public:
        StarHollowMulti(fatpound::win32::d3d11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}