module;

#include <chrono>

module FatPound.Util.AutoTimer;

namespace fatpound::util
{
    float AutoTimer::Mark() noexcept
    {
        const auto old = m_last_;

        m_last_ = std::chrono::steady_clock::now();

        const std::chrono::duration<float> frame_time = m_last_ - old;

        return frame_time.count();
    }
    float AutoTimer::Peek() const noexcept
    {
        const auto& now = std::chrono::steady_clock::now();

        return std::chrono::duration<float>(now - m_last_).count();
    }
}