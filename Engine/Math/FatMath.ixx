module;

export module FatMath;

import <cassert>;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}