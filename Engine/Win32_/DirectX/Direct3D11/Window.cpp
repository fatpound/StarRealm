module;

#include "../../FatWin32_.hpp"

#if IN_RELEASE
#define CLIENT_WIDTH    width_
#define CLIENT_HEIGHT   height_
#define WIDTH           CLIENT_WIDTH
#define HEIGHT          CLIENT_HEIGHT
#else
#define WINDOW_WIDTH    (rect.right - rect.left)
#define WINDOW_HEIGHT   (rect.bottom - rect.top)
#define WIDTH           WINDOW_WIDTH
#define HEIGHT          WINDOW_HEIGHT
#endif // IN_RELEASE

module FatPound.Win32.Direct3D11.Window;

namespace fatpound::win32::d3d11
{
    // Window

    Window::Window(const wchar_t* const title, std::size_t width, std::size_t height)
        :
        width_(width),
        height_(height)
    {
#if IN_RELEASE

        hWnd_ = CreateWindow(
            WndClass_::GetName(),
            title,
            WS_POPUP,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<int>(WIDTH),
            static_cast<int>(HEIGHT),
            nullptr,
            nullptr,
            WndClass_::GetInstance(),
            this
        );

#else

        RECT rect = {};
        rect.left = 150;
        rect.right = static_cast<LONG>(width_) + rect.left;
        rect.top = 150;
        rect.bottom = static_cast<LONG>(height_) + rect.top;

        AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
        
        hWnd_ = CreateWindow(
            WndClass_::GetName(),
            title,
            WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
            rect.left,
            rect.top,
            static_cast<int>(WIDTH),
            static_cast<int>(HEIGHT),
            nullptr,
            nullptr,
            WndClass_::GetInstance(),
            this
        );

#endif // IN_RELEASE

        if (hWnd_ == nullptr) [[unlikely]]
        {
            throw std::runtime_error("Error occured when creating HWND!");
        }

        pGfx_ = std::make_unique<Graphics>(hWnd_, WIDTH, HEIGHT);

        if (pGfx_ == nullptr) [[unlikely]]
        {
            throw std::runtime_error("Error occured when creating Graphics!");
        }

        ShowWindow(hWnd_, /*SW_SHOW*/ SW_SHOWDEFAULT);
        UpdateWindow(hWnd_);
    }
    Window::~Window()
    {
        DestroyWindow(hWnd_);
    }

    auto Window::ProcessMessages() noexcept -> std::optional<WPARAM>
    {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) [[unlikely]]
            {
                return msg.wParam;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return {};
    }

    Graphics& Window::Gfx()
    {
        return *pGfx_;
    }

    bool Window::IsActive() const noexcept
    {
        return GetActiveWindow() == hWnd_;
    }
    bool Window::IsMinimized() const noexcept
    {
        return IsIconic(hWnd_) != 0;
    }

    void Window::SetTitle(const std::wstring& title)
    {
        if (SetWindowText(hWnd_, title.c_str()) == 0) [[unlikely]]
        {
            throw std::runtime_error("Could NOT set the Window Text!");
        }
    }
    void Window::ShowMessageBox(const std::wstring& message, const std::wstring& title, UINT error_flags) noexcept
    {
        MessageBox(hWnd_, message.c_str(), title.c_str(), error_flags);
    }
    void Window::Kill()
    {
        PostQuitMessage(0);
    }

    LRESULT CALLBACK Window::HandleMsgSetup_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk_));

            return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    LRESULT CALLBACK Window::HandleMsgThunk_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

        return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
    }

    LRESULT Window::HandleMsg_(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        switch (msg)
        {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_KILLFOCUS:
            kbd.ClearKeyStateBitset_();
            break;

            /******** KEYBOARD MESSAGES ********/
        case WM_KEYDOWN: [[fallthrough]];
        case WM_SYSKEYDOWN:
            if (!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled())
            {
                kbd.OnKeyPressed_(static_cast<unsigned char>(wParam));
            }
            break;

        case WM_KEYUP: [[fallthrough]];
        case WM_SYSKEYUP:
            kbd.OnKeyReleased_(static_cast<unsigned char>(wParam));
            break;

        case WM_CHAR:
            kbd.OnChar_(static_cast<unsigned char>(wParam));
            break;
            /******** END KEYBOARD MESSAGES ********/


            /******** MOUSE MESSAGES ********/
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);

            if (pt.x >= 0 && pt.x < width_ && pt.y >= 0 && pt.y < height_)
            {
                mouse.OnMouseMove_(pt.x, pt.y);

                if (not mouse.IsInWindow())
                {
                    SetCapture(hWnd);
                    mouse.OnMouseEnter_();
                }
            }
            else
            {
                if (wParam & (MK_LBUTTON | MK_RBUTTON))
                {
                    mouse.OnMouseMove_(pt.x, pt.y);
                }
                else
                {
                    ReleaseCapture();
                    mouse.OnMouseLeave_();
                }
            }
        }
        break;

        case WM_LBUTTONDOWN:
            mouse.OnLeftPressed_();
            break;

        case WM_LBUTTONUP:
            mouse.OnLeftReleased_();
            break;

        case WM_RBUTTONDOWN:
            mouse.OnRightPressed_();
            break;

        case WM_RBUTTONUP:
            mouse.OnRightReleased_();
            break;

        case WM_MBUTTONDOWN:
            mouse.OnWheelPressed_();
            break;

        case WM_MBUTTONUP:
            mouse.OnWheelReleased_();
            break;

        case WM_MOUSEWHEEL:
            mouse.OnWheelDelta_(GET_WHEEL_DELTA_WPARAM(wParam));
            break;
            /******* END MOUSE MESSAGES *******/

        default:
            break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
    }


    // WndClass_

    Window::WndClass_::WndClass_() noexcept
        :
        hInst_(GetModuleHandle(nullptr))
    {
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = &Window::HandleMsgSetup_;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInst_;
        wc.hIcon = nullptr;
        wc.hIconSm = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = WndClass_::wndClassName_;

        if constexpr (Window::cursor_enabled_)
        {
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        }
        else
        {
            ShowCursor(false);
        }

        RegisterClassEx(&wc);
    }
    Window::WndClass_::~WndClass_()
    {
        UnregisterClass(WndClass_::wndClassName_, WndClass_::GetInstance());
    }

    HINSTANCE Window::WndClass_::GetInstance() noexcept
    {
        static WndClass_ wndClass_;

        return wndClass_.hInst_;
    }

    const wchar_t* const Window::WndClass_::GetName() noexcept
    {
        return wndClassName_;
    }
}