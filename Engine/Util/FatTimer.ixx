module;

#ifndef NDEBUG
#include <chrono>
#endif // !NDEBUG

export module FatTimer;

#ifdef NDEBUG
import std.core;
#endif // NDEBUG

export namespace fatpound::util
{
    class Timer final
    {
    public:
        float Mark() noexcept;
        float Peek() const noexcept;


    protected:


    private:
        std::chrono::steady_clock::time_point last_ = std::chrono::steady_clock::now();
    };
}