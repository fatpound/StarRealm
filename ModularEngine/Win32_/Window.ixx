module;

#include "FatWin32_.hpp"

export module FatPound.Win32.Window;

import FatPound.Win32.IO;
import FatPound.Math;

import std;

export namespace fatpound::win32
{
    class Window final
    {
#ifdef UNICODE
        using str_t = const wchar_t* const;
#else
        using str_t = const char* const;
#endif // UNICODE

    public:
        struct ClientSizeInfo final
        {
            unsigned int width;
            unsigned int height;
        };


    public:
        Window(str_t title, const ClientSizeInfo& dimensions);

        Window() = delete;
        Window(const Window& src) = delete;
        Window& operator = (const Window& src) = delete;

        Window(Window&& src) = delete;
        Window& operator = (Window&& src) = delete;
        ~Window() noexcept;


    public:
        static auto ProcessMessages() noexcept -> std::optional<WPARAM>;


    public:
        template <NAMESPACE_MATH::Number N>
        auto GetClientWidth() const noexcept
        {
            return static_cast<N>(client_size_.width);
        }
        template <NAMESPACE_MATH::Number N>
        auto GetClientHeight() const noexcept
        {
            return static_cast<N>(client_size_.height);
        }

        auto GetHwnd() const noexcept -> HWND;

        bool IsActive() const noexcept;
        bool IsMinimized() const noexcept;

        void SetTitle(const std::wstring& title);
        void ShowMessageBox(const std::wstring& message, const std::wstring& title, UINT error_flags) noexcept;
        void Kill();


    public:
        NAMESPACE_IO::Keyboard kbd;
        NAMESPACE_IO::Mouse mouse;

        
    protected:


    private:
        class WndClass_ final
        {
        public:
            static auto GetInstance() noexcept -> HINSTANCE;

            static auto GetName() noexcept -> str_t;

        protected:

        private:
            WndClass_() noexcept;
            WndClass_(const WndClass_& src) = delete;
            WndClass_& operator = (const WndClass_& src) = delete;

            WndClass_(WndClass_&& src) = delete;
            WndClass_& operator = (WndClass_&& src) = delete;
            ~WndClass_();

        private:
            HINSTANCE hInst_;

#ifdef UNICODE
            static constexpr str_t wndClassName_ = L"FatPound Default WndClass";
#else
            static constexpr str_t wndClassName_ =  "FatPound Default WndClass";
#endif // UNICODE
        };


    private:
        static LRESULT CALLBACK HandleMsgSetup_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        LRESULT HandleMsg_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        HWND hWnd_;

        const ClientSizeInfo client_size_;

        static constexpr bool cursor_enabled_ = true;
    };
}