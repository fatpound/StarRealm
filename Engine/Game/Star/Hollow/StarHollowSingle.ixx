module;

#include "../../../Win32_/FatWin32_.hpp"

export module StarHollowSingle;

import D3D11Graphics;
import StarBase;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
import std.core;
import std.memory;
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::starrealm
{
    class StarHollowSingle final : public StarBase<StarHollowSingle>
    {
    public:
        StarHollowSingle(NAMESPACE_D3D11::Graphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}