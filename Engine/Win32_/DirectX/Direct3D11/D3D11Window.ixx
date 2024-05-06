module;

#include "../../FatWin32_.hpp"

export module D3D11Window;

import D3D11Graphics;
import Keyboard;
import Mouse;
import FatMath;

#if _MSVC_LANG > 202002L
import std;
#else
#if _MSVC_LANG == 202002L
#ifdef NDEBUG
import std.core;
import std.memory;
#else
import <vector>;
import <optional>;
import <string>;
import <memory>;
//
import <sstream>;
import <stdexcept>;
#endif // NDEBUG
#else
#error C++20 or greater version required
#endif // _MSVC_LANG == 202002L
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32::d3d11
{
    class Window final
    {
    public:
        Window(const wchar_t* const window_title, std::size_t width, std::size_t height);

        Window() = delete;
        Window(const Window& src) = delete;
        Window& operator = (const Window& src) = delete;
        Window(Window&& src) = delete;
        Window& operator = (Window&& src) = delete;
        ~Window();


    public:
        static std::optional<WPARAM> ProcessMessages() noexcept;

        Graphics& Gfx();

        template <fatpound::math::Number N>
        N GetWidth() noexcept
        {
            return static_cast<N>(screen_width_);
        }

        template <fatpound::math::Number N>
        N GetHeight() noexcept
        {
            return static_cast<N>(screen_height_);
        }

        bool IsActive() const;
        bool IsMinimized() const;

        void SetTitle(const std::wstring& title);
        void ShowMessageBox(const std::wstring& message, const std::wstring& title, UINT error_flags);
        void Kill();


    public:
        fatpound::win32::io::Keyboard kbd;
        fatpound::win32::io::Mouse mouse;


    protected:


    private:
        static LRESULT CALLBACK HandleMsgSetup_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;


    private:
        HWND hWnd_;
        HINSTANCE hInst_;

        std::unique_ptr<Graphics> pGfx_;

        const std::size_t screen_width_;
        const std::size_t screen_height_;

        static constexpr bool cursor_enabled_ = true;

        static constexpr auto wndClassName_ = L"Fat Direct3D11 Engine Window Class";
    };
}