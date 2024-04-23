module;

#include "../../../../Win32_/FatWin32_.hpp"

#include <DirectXMath.h>

export module StarFilledBlend;

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
    class StarFilledBlend final : public StarBase<StarFilledBlend>
    {
    public:
        StarFilledBlend(fatpound::dx11::D3DGraphics& gfx, const Descriptor& desc);


    protected:


    private:
    };
}