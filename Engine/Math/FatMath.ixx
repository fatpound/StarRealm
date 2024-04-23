// module;

export module FatMath;

import <cassert>;

#ifdef NDEBUG
import std.core;
#else
import <cmath>;
/**/
import <limits>;
import <numeric>;
import <numbers>;
import <concepts>;
#endif // NDEBUG

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}