module;

#include <FatWin32_.hpp>

export module FatPound.Win32.Window;

import FatPound.Win32.IO;
import FatPound.Math;
import FatPound.Util;

import std;

export namespace fatpound::win32
{
    class Window final
    {
#ifdef UNICODE
        using str_t = const wchar_t*;
#else
        using str_t = const char*;
#endif // UNICODE

    public:
        explicit Window(const str_t title, const NAMESPACE_UTIL::ScreenSizeInfo& dimensions);

        explicit Window() = delete;
        explicit Window(const Window& src) = delete;
        explicit Window(Window&& src) = delete;

        Window& operator = (const Window& src) = delete;
        Window& operator = (Window&& src) = delete;
        ~Window() noexcept;


    public:
        auto operator <=> (const Window& rhs) const = delete;
        bool operator ==  (const Window& rhs) const = delete;


    public:
        static auto ProcessMessages() noexcept -> std::optional<WPARAM>;


    public:
        auto GetMouse()    noexcept -> NAMESPACE_IO::Mouse&;
        auto GetKeyboard() noexcept -> NAMESPACE_IO::Keyboard&;

        auto GetHwnd() const noexcept -> HWND;

        bool IsActive() const noexcept;
        bool IsMinimized() const noexcept;

        void SetTitle(const std::wstring& title);
        void ShowMessageBox(const std::wstring& message, const std::wstring& title, UINT error_flags) noexcept;
        void Kill() noexcept;


    public:
        template <NAMESPACE_MATH::Number N>
        auto GetClientWidth() const noexcept
        {
            return static_cast<N>(m_client_size_.m_width);
        }

        template <NAMESPACE_MATH::Number N>
        auto GetClientHeight() const noexcept
        {
            return static_cast<N>(m_client_size_.m_height);
        }

        
    protected:


    private:
        class WndClass_ final
        {
        public:
            static auto GetInstance() noexcept -> HINSTANCE;

            static auto GetName() noexcept -> str_t;

        public:
            auto operator <=> (const WndClass_& rhs) const = delete;
            bool operator ==  (const WndClass_& rhs) const = delete;

        protected:

        private:
            explicit WndClass_() noexcept;
            explicit WndClass_(const WndClass_& src) = delete;
            explicit WndClass_(WndClass_&& src) = delete;

            WndClass_& operator = (const WndClass_& src) = delete;
            WndClass_& operator = (WndClass_&& src) = delete;
            ~WndClass_();

        private:
            HINSTANCE m_hInst_;

#ifdef UNICODE
            static constexpr str_t s_wndClassName_ = L"FatPound Default WndClass";
#else
            static constexpr str_t s_wndClassName_ =  "FatPound Default WndClass";
#endif // UNICODE
        };


    private:
        static auto CALLBACK HandleMsgSetup_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT;
        static auto CALLBACK HandleMsgThunk_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT;


    private:
        auto HandleMsg_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT;


    private:
        HWND m_hWnd_;

        const NAMESPACE_UTIL::ScreenSizeInfo m_client_size_;

        NAMESPACE_IO::Mouse m_mouse_;
        NAMESPACE_IO::Keyboard m_keyboard_;

        static constexpr bool s_cursorEnabled_ = true;
    };
}