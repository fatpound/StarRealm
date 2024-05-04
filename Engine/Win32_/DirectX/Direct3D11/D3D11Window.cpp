module;

#include "../../FatWin32_.hpp"

module D3D11Window;

namespace fatpound::win32::d3d11
{
    Window::Window(const wchar_t* const window_title, std::size_t width, std::size_t height)
        :
        hInst_(GetModuleHandle(nullptr)),
        screen_width_(width),
        screen_height_(height)
    {
        WNDCLASSEX wc = { 0 };

        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = &HandleMsgSetup_;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInst_;
        wc.hIcon = nullptr;
        wc.hCursor = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = wndClassName_;
        wc.hIconSm = nullptr;

        RegisterClassEx(&wc);

#ifdef NDEBUG

        hWnd_ = CreateWindow(
            wndClassName_,
            window_title,
            WS_POPUP,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<int>(screen_width_),
            static_cast<int>(screen_height_),
            nullptr,
            nullptr,
            hInst_,
            this
        );

#else

        RECT rect = {};
        rect.left = 0;
        rect.right = static_cast<LONG>(screen_width_) + rect.left;
        rect.top = 0;
        rect.bottom = static_cast<LONG>(screen_height_) + rect.top;

        AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

        hWnd_ = CreateWindow(
            wndClassName_,
            window_title,
            WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            nullptr,
            nullptr,
            hInst_,
            this
        );

#endif // NDEBUG

        if (hWnd_ == nullptr)
        {
            throw;
        }

#ifdef NDEBUG
        pGfx_ = std::make_unique<Graphics>(hWnd_, screen_width_, screen_height_);
#else
        pGfx_ = std::make_unique<Graphics>(hWnd_, rect.right - rect.left, rect.bottom - rect.top);
#endif // NDEBUG

        if (pGfx_ == nullptr)
        {
            throw;
        }

        ShowWindow(hWnd_, /*SW_SHOW*/ SW_SHOWDEFAULT);
        SetCursor(LoadCursor(nullptr, IDC_ARROW));
    }
    Window::~Window()
    {
        DestroyWindow(hWnd_);
        UnregisterClass(wndClassName_, hInst_);
    }

    std::optional<int> Window::ProcessMessages() noexcept
    {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                return static_cast<int>(msg.wParam);
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return {};
    }

    Graphics& Window::Gfx()
    {
        if (pGfx_ == nullptr)
        {
            throw;
        }

        return *pGfx_;
    }

    void Window::SetTitle(const std::wstring& title)
    {
        if (SetWindowText(hWnd_, title.c_str()) == 0)
        {
            throw;
        }
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
        case WM_KEYDOWN:
            [[fallthrough]];
            
        [[likely]] case WM_SYSKEYDOWN:
            if (!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled())
            {
                kbd.OnKeyPressed_(static_cast<unsigned char>(wParam));
            }
            break;

        case WM_KEYUP:
            [[fallthrough]];

            
        [[likely]] case WM_SYSKEYUP:
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

            if (pt.x >= 0 && pt.x < screen_width_ && pt.y >= 0 && pt.y < screen_height_)
            {
                mouse.OnMouseMove_(pt.x, pt.y);

                if (!mouse.IsInWindow())
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
}