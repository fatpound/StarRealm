module;

export module AutoTimer;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
import std.core;
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
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