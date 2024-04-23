module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <d3d11.h>
#include <DirectXMath.h>

export module StarFilledMulti;

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
    class StarFilledMulti final : public StarBase<StarFilledMulti>
    {
    public:
        StarFilledMulti(fatpound::dx11::D3DGraphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}