module;

export module FatPound.Util.AutoTimer;

import std;

export namespace fatpound::util
{
    class AutoTimer final
    {
    public:
        explicit AutoTimer() = default;
        explicit AutoTimer(const AutoTimer& src) = delete;
        explicit AutoTimer(AutoTimer&& src) = delete;

        AutoTimer& operator = (const AutoTimer& src) = delete;
        AutoTimer& operator = (AutoTimer&& src) = delete;
        ~AutoTimer() noexcept = default;


    public:
        float Mark() noexcept;
        float Peek() const noexcept;


    protected:


    private:
        std::chrono::steady_clock::time_point m_last_ = std::chrono::steady_clock::now();
    };
}