module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowMulti;

import D3D11Graphics;
import StarBase;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#if IN_RELEASE
import std.core;
import std.memory;
#else
import <vector>;
import <memory>;
//
import <random>;
import <algorithm>;
import <numeric>;
#endif // IN_RELEASE
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

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