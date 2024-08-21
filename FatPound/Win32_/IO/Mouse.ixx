module;

#include <FatWin32_Namespaces.hpp>

export module FatPound.Win32.IO.Mouse;

import std;

namespace fatpound::win32
{
    class Window;
}

export namespace fatpound::win32::io
{
    class Mouse final
    {
        friend NAMESPACE_WIN32::Window;

    public:
        struct RawDelta final
        {
            int x;
            int y;
        };


    public:
        class Event final
        {
        public:
            enum class Type
            {
                LPress,
                LRelease,
                RPress,
                RRelease,
                WheelPress,
                WheelRelease,
                WheelUp,
                WheelDown,
                Enter,
                Move,
                Leave,
                Invalid
            };

        public:
            explicit Event(Type type, const Mouse& parent) noexcept;

            explicit Event() = default;
            Event(const Event& src) = default;
            Event(Event&& src) = default;

            Event& operator = (const Event& src) = default;
            Event& operator = (Event&& src) = default;
            ~Event() = default;

        public:
            auto operator <=> (const Event& rhs) const = delete;
            bool operator ==  (const Event& rhs) const = delete;

        public:
            auto GetPos() const noexcept -> std::pair<int, int>;

            Type GetType() const noexcept;

            int GetPosX() const noexcept;
            int GetPosY() const noexcept;

            bool IsValid() const noexcept;
            bool LeftIsPressed() const noexcept;
            bool RightIsPressed() const noexcept;
            bool WheelIsPressed() const noexcept;

        protected:

        private:
            Type type_ = Type::Invalid;

            int x_{};
            int y_{};

            bool  left_is_pressed_{false};
            bool right_is_pressed_{false};
            bool wheel_is_pressed_{false};
        };


    public:
        explicit Mouse() = default;
        explicit Mouse(const Mouse& src) = delete;
        explicit Mouse(Mouse&& src) = delete;

        Mouse& operator = (const Mouse& src) = delete;
        Mouse& operator = (Mouse&& src) = delete;
        ~Mouse() noexcept = default;


    public:
        auto operator <=> (const Mouse& rhs) const = delete;
        bool operator ==  (const Mouse& rhs) const = delete;


    public:
        auto GetPos() const noexcept -> std::pair<int, int>;

        auto ReadRawDelta() noexcept -> std::optional<RawDelta>;

        Event ReadFromBuffer() noexcept;

        int GetPosX() const noexcept;
        int GetPosY() const noexcept;

        bool EventBufferIsEmpty() const noexcept;
        bool IsInWindow() const noexcept;

        bool  LeftIsPressed() const noexcept;
        bool RightIsPressed() const noexcept;
        bool WheelIsPressed() const noexcept;

        void FlushBuffer() noexcept;


    protected:


    private:
        void OnMouseMove_(int x, int y);
        void OnMouseEnter_();
        void OnMouseLeave_();

        void OnRawDelta_(int dx, int dy);

        void OnLeftPressed_();
        void OnLeftReleased_();
        void OnRightPressed_();
        void OnRightReleased_();
        void OnWheelPressed_();
        void OnWheelReleased_();
        void OnWheelUp_();
        void OnWheelDown_();
        void OnWheelDelta_(int delta);

        void TrimBuffer_() noexcept;
        void TrimRawInputBuffer_() noexcept;


    private:
        std::queue<Event> m_event_buffer_;
        std::queue<RawDelta> m_raw_delta_buffer_;

        int m_x_ = 0;
        int m_y_ = 0;
        int m_wheel_delta_carry_ = 0;

        bool m_is_in_window_ = false;

        bool  m_left_is_pressed_ = false;
        bool m_right_is_pressed_ = false;
        bool m_wheel_is_pressed_ = false;

        static constexpr unsigned int s_bufferSize_ = 16u;
    };
}