module;

export module Keyboard;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
#else
import <bitset>;
import <queue>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

namespace fatpound::win32::d3d11
{
    class Window;
}

export namespace fatpound::win32::io
{
    class Keyboard final
    {
        friend class fatpound::win32::d3d11::Window;

    public:
        Keyboard() = default;
        Keyboard(const Keyboard& src) = delete;
        Keyboard& operator = (const Keyboard& src) = delete;
        Keyboard(Keyboard&& src) = delete;
        Keyboard& operator = (Keyboard&& src) = delete;
        ~Keyboard() = default;


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
            Event() noexcept;

            Event(Type type, unsigned char code) noexcept;

        public:
            unsigned char GetCode() const noexcept;

            bool IsPress() const noexcept;
            bool IsRelease() const noexcept;
            bool IsInvalid() const noexcept;

        protected:

        private:
            Type type_;

            unsigned char code_;
        };


    public:
        Event ReadKeyFromBuffer() noexcept;

        char ReadCharFromBuffer() noexcept;

        bool AutoRepeatIsEnabled() const noexcept;
        bool CharBufferIsEmpty() const noexcept;
        bool KeyBufferIsEmpty() const noexcept;
        bool KeyIsPressed(unsigned char keycode) const noexcept;

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
            while (buffer.size() > bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        void OnKeyPressed_(unsigned char keycode) noexcept;
        void OnKeyReleased_(unsigned char keycode) noexcept;
        void OnChar_(char character) noexcept;

        void ClearKeyStateBitset_() noexcept;


    private:
        static constexpr unsigned int keyCount_ = 256u;
        static constexpr unsigned int bufferSize_ = 16u;

        std::bitset<keyCount_> keystates_;

        std::queue<Event> keybuffer_;
        std::queue<char> charbuffer_;

        bool autoRepeatEnabled_ = false;
    };
}