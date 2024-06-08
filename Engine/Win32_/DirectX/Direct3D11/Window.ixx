module;

#include "../../FatWin32_.hpp"

export module Direct3D11.Window;

import Direct3D11.Graphics;
import Keyboard;
import Mouse;
import FatMath;

import std;

export namespace fatpound::win32::d3d11
{
    class Window final
    {
    public:
        Window(const wchar_t* const title, std::size_t width, std::size_t height);

        Window() = delete;
        Window(const Window& src) = delete;
        Window& operator = (const Window& src) = delete;
        Window(Window&& src) = delete;
        Window& operator = (Window&& src) = delete;
        ~Window();


    public:
        static auto ProcessMessages() noexcept -> std::optional<WPARAM>;


    public:
        template <NAMESPACE_MATH::Number N>
        N GetWidth() const noexcept
        {
            return static_cast<N>(width_);
        }

        template <NAMESPACE_MATH::Number N>
        N GetHeight() const noexcept
        {
            return static_cast<N>(height_);
        }

        Graphics& Gfx();

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
            static HINSTANCE GetInstance() noexcept;

            static const wchar_t* const GetName() noexcept;

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

            static constexpr auto wndClassName_ = L"FatPound Direct3D11 Engine Window";
        };


    private:
        static LRESULT CALLBACK HandleMsgSetup_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        LRESULT HandleMsg_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        HWND hWnd_;

        std::unique_ptr<Graphics> pGfx_;

        const std::size_t width_;
        const std::size_t height_;

        static constexpr bool cursor_enabled_ = true;
    };
}