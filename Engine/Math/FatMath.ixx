module;

export module FatMath;

import <cassert>;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
import std.core;
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}