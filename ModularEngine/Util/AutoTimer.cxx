module;

// #include <chrono>

// cant include this since it leads to an ICE in MSVC v19.40.33807
// but that's not a problem
// because the IntelliSense "errors" are shown in this .cpp file
// so it doesn't break IntelliSense
// text editor coloring works fine, other IntelliSense features are working fine
// it is OK for now in VS 2022 17.10.0

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