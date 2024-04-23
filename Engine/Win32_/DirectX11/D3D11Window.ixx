module;

#include "../FatWin32_.hpp"

export module D3D11Window;

import D3D11Graphics;
import Keyboard;
import Mouse;
import FatMath;

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

export namespace fatpound::dx11
{
    class D3DWindow final
    {
    public:
        D3DWindow(const wchar_t* const window_title, std::size_t width, std::size_t height);

        D3DWindow() = delete;
        D3DWindow(const D3DWindow& src) = delete;
        D3DWindow(D3DWindow&& src) = delete;
        D3DWindow& operator = (const D3DWindow& src) = delete;
        D3DWindow& operator = (D3DWindow&& src) = delete;
        ~D3DWindow();


    public:
        static std::optional<int> ProcessMessages() noexcept;

        D3DGraphics& Gfx();

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

        void SetTitle(const std::wstring& title);
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

        std::unique_ptr<D3DGraphics> pGfx_;

        std::vector<BYTE> rawBuffer_;

        const std::size_t screen_width_;
        const std::size_t screen_height_;

        bool cursor_enabled_ = false;

        static constexpr const auto* const wndClassName_ = L"Fat Direct3D11 Engine Window Class";
    };
}