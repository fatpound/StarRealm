module;

export module AutoTimer;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

export namespace fatpound::util
{
    class AutoTimer final
    {
    public:
        float Mark() noexcept;
        float Peek() const noexcept;


    protected:


    private:
        std::chrono::steady_clock::time_point last_ = std::chrono::steady_clock::now();
    };
}