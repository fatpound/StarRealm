module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

export module StarHollowBlend;

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
#endif // NDEBUG

export namespace fatpound::starrealm
{
    class StarHollowBlend final : public StarBase<StarHollowBlend>
    {
    public:
        StarHollowBlend(fatpound::dx11::D3DGraphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}