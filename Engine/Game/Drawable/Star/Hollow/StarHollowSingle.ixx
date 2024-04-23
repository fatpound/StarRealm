module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

export module StarHollowSingle;

import D3D11Graphics;
import StarBase;

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

export namespace fatpound::starrealm
{
    class StarHollowSingle final : public StarBase<StarHollowSingle>
    {
    public:
        StarHollowSingle(fatpound::dx11::D3DGraphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}