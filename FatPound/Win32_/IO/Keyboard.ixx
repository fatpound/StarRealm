module;

#include <FatWin32_Namespaces.hpp>

export module FatPound.Win32.IO.Keyboard;

import std;

namespace fatpound::win32
{
    class Window;
}

export namespace fatpound::win32::io
{
    class Keyboard final
    {
        friend NAMESPACE_WIN32::Window;

    public:
        class Event final
        {
        public:
            enum class Type
            {
                Press,
                Release,
                Invalid
            };

        public:
            explicit Event(Type type, unsigned char code) noexcept;

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
            unsigned char GetCode() const noexcept;

            bool IsPress() const noexcept;
            bool IsRelease() const noexcept;
            bool IsInvalid() const noexcept;

        protected:

        private:
            Type m_type_ = Type::Invalid;

            unsigned char m_code_ = 0u;
        };


    public:
        explicit Keyboard() = default;
        explicit Keyboard(const Keyboard& src) = delete;
        explicit Keyboard(Keyboard&& src) = delete;

        Keyboard& operator = (const Keyboard& src) = delete;
        Keyboard& operator = (Keyboard&& src) = delete;
        ~Keyboard() noexcept = default;


    public:
        auto operator <=> (const Keyboard& rhs) const = delete;
        bool operator ==  (const Keyboard& rhs) const = delete;


    public:
        Event ReadKeyFromBuffer() noexcept;

        auto ReadCharFromBuffer() noexcept -> unsigned char;

        bool KeyIsPressed(unsigned char keycode) const noexcept;
        bool KeyBufferIsEmpty() const noexcept;
        bool CharBufferIsEmpty() const noexcept;
        bool AutoRepeatIsEnabled() const noexcept;

        void FlushKeyBuffer() noexcept;
        void FlushCharBuffer() noexcept;
        void FlushBuffers() noexcept;
        void EnableAutoRepeat() noexcept;
        void DisableAutoRepeat() noexcept;


    protected:


    private:
        template <typename T>
        static void TrimBuffer_(std::queue<T>& buffer) noexcept
        {
            while (buffer.size() > s_bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        void OnKeyPressed_(unsigned char keycode);
        void OnKeyReleased_(unsigned char keycode);
        void OnChar_(unsigned char character);

        void ClearKeyStateBitset_() noexcept;


    private:
        static constexpr unsigned int s_keyCount_ = 256u;

        std::bitset<s_keyCount_> m_key_states_;
        
        std::queue<Event> m_event_buffer_;
        std::queue<unsigned char> m_char_buffer_;

        bool m_auto_repeat_enabled_ = false;

        static constexpr unsigned int s_bufferSize_ = 16u;
    };
}