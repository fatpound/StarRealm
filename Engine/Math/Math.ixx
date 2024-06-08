module;

export module FatPound.Math;

import std;

export namespace fatpound::math
{
    template <typename T>
    concept Number = std::integral<T> || std::floating_point<T>;
}