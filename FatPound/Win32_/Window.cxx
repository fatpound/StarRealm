module;

#include <FatWin32_.hpp>

#define WINDOW_RECT_WIDTH       (rect.right - rect.left)
#define WINDOW_RECT_HEIGHT      (rect.bottom - rect.top)

#define CLIENT_WIDTH            static_cast<LONG>(m_client_size_.m_width)
#define CLIENT_HEIGHT           static_cast<LONG>(m_client_size_.m_height)

#if IN_RELEASE

#define WINDOW_WIDTH            CLIENT_WIDTH
#define WINDOW_HEIGHT           CLIENT_HEIGHT
#define WINDOW_STYLE            WS_POPUP
#define WINDOW_POSITION_X       CW_USEDEFAULT
#define WINDOW_POSITION_Y       CW_USEDEFAULT

#else

#define WINDOW_WIDTH            WINDOW_RECT_WIDTH
#define WINDOW_HEIGHT           WINDOW_RECT_HEIGHT
#define WINDOW_STYLE            WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX
#define WINDOW_POSITION_X       rect.left
#define WINDOW_POSITION_Y       rect.top

#endif // IN_RELEASE

module FatPound.Win32.Window;

namespace fatpound::win32
{
    // Window

    Window::Window(const str_t title, const NAMESPACE_UTIL::ScreenSizeInfo& dimensions)
        :
        m_client_size_{ dimensions }
    {
#if IN_DEBUG

        RECT rect = {};
        rect.left = 150;
        rect.right = CLIENT_WIDTH + rect.left;
        rect.top = 150;
        rect.bottom = CLIENT_HEIGHT + rect.top;

        ::AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

#endif // IN_DEBUG

        m_hWnd_ = ::CreateWindow(
            WndClass_::GetName(),
            title,
            WINDOW_STYLE,
            WINDOW_POSITION_X,
            WINDOW_POSITION_Y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            nullptr,
            nullptr,
            WndClass_::GetInstance(),
            this
        );

        if (m_hWnd_ == nullptr) [[unlikely]]
        {
            throw std::runtime_error("Error occured when creating HWND!");
        }

        ::ShowWindow(m_hWnd_, SW_SHOWDEFAULT);
        ::UpdateWindow(m_hWnd_);
    }
    Window::~Window()
    {
        ::DestroyWindow(m_hWnd_);
    }

    auto Window::ProcessMessages() noexcept -> std::optional<WPARAM>
    {
        MSG msg;

        while (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) [[unlikely]]
            {
                return msg.wParam;
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return std::nullopt;
    }

    auto Window::GetMouse() noexcept -> NAMESPACE_IO::Mouse&
    {
        return m_mouse_;
    }
    auto Window::GetKeyboard() noexcept -> NAMESPACE_IO::Keyboard&
    {
        return m_keyboard_;
    }

    auto Window::GetHwnd() const noexcept -> HWND
    {
        return m_hWnd_;
    }

    bool Window::IsActive() const noexcept
    {
        return ::GetActiveWindow() == m_hWnd_;
    }
    bool Window::IsMinimized() const noexcept
    {
        return ::IsIconic(m_hWnd_) != 0;
    }

    void Window::SetTitle(const std::wstring& title)
    {
        if (::SetWindowText(m_hWnd_, title.c_str()) == 0) [[unlikely]]
        {
            throw std::runtime_error("Could NOT set the Window Text!");
        }
    }
    void Window::ShowMessageBox(const std::wstring& message, const std::wstring& title, UINT error_flags) noexcept
    {
        ::MessageBox(m_hWnd_, message.c_str(), title.c_str(), error_flags);
    }
    void Window::Kill() noexcept
    {
        ::PostQuitMessage(0);
    }

    auto CALLBACK Window::HandleMsgSetup_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT
    {
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            ::SetWindowLongPtr(hWnd, GWLP_WNDPROC,  reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk_));

            return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
        }

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
    auto CALLBACK Window::HandleMsgThunk_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT
    {
        Window* const pWnd = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

        return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
    }

    auto Window::HandleMsg_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept -> LRESULT
    {
        switch (msg)
        {
        case WM_CLOSE:
            ::PostQuitMessage(0);
            return 0;

        case WM_KILLFOCUS:
            m_keyboard_.ClearKeyStateBitset_();
            break;

            /******** KEYBOARD MESSAGES ********/
        case WM_KEYDOWN: [[fallthrough]];
        case WM_SYSKEYDOWN:
            if (!(lParam & 0x40000000) || m_keyboard_.AutoRepeatIsEnabled())
            {
                m_keyboard_.OnKeyPressed_(static_cast<unsigned char>(wParam));
            }
            break;

        case WM_KEYUP: [[fallthrough]];
        case WM_SYSKEYUP:
            m_keyboard_.OnKeyReleased_(static_cast<unsigned char>(wParam));
            break;

        case WM_CHAR:
            m_keyboard_.OnChar_(static_cast<unsigned char>(wParam));
            break;
            /******** END KEYBOARD MESSAGES ********/


            /******** MOUSE MESSAGES ********/
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);

            if (pt.x >= 0 &&
                pt.x < static_cast<SHORT>(m_client_size_.m_width) &&
                pt.y >= 0 &&
                pt.y < static_cast<SHORT>(m_client_size_.m_height)
            )
            {
                m_mouse_.OnMouseMove_(pt.x, pt.y);

                if (not m_mouse_.IsInWindow())
                {
                    ::SetCapture(hWnd);
                    m_mouse_.OnMouseEnter_();
                }
            }
            else
            {
                if (wParam & (MK_LBUTTON | MK_RBUTTON))
                {
                    m_mouse_.OnMouseMove_(pt.x, pt.y);
                }
                else
                {
                    ::ReleaseCapture();
                    m_mouse_.OnMouseLeave_();
                }
            }
        }
        break;

        case WM_LBUTTONDOWN:
            m_mouse_.OnLeftPressed_();
            break;

        case WM_LBUTTONUP:
            m_mouse_.OnLeftReleased_();
            break;

        case WM_RBUTTONDOWN:
            m_mouse_.OnRightPressed_();
            break;

        case WM_RBUTTONUP:
            m_mouse_.OnRightReleased_();
            break;

        case WM_MBUTTONDOWN:
            m_mouse_.OnWheelPressed_();
            break;

        case WM_MBUTTONUP:
            m_mouse_.OnWheelReleased_();
            break;

        case WM_MOUSEWHEEL:
            m_mouse_.OnWheelDelta_(GET_WHEEL_DELTA_WPARAM(wParam));
            break;
            /******* END MOUSE MESSAGES *******/

        default:
            break;
        }

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }


    // Window::WndClass_

    Window::WndClass_::WndClass_() noexcept
        :
        m_hInst_(::GetModuleHandle(nullptr))
    {
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(wc);
        wc.style = CS_OWNDC;
        wc.lpfnWndProc = &Window::HandleMsgSetup_;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_hInst_;
        wc.hIcon = nullptr;
        wc.hIconSm = nullptr;
        wc.hbrBackground = nullptr;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = s_wndClassName_;

        if constexpr (s_cursorEnabled_)
        {
            wc.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        }
        else
        {
            ::ShowCursor(false);
        }

        ::RegisterClassEx(&wc);
    }
    Window::WndClass_::~WndClass_()
    {
        ::UnregisterClass(s_wndClassName_, WndClass_::GetInstance());
    }

    auto Window::WndClass_::GetInstance() noexcept -> HINSTANCE
    {
        static WndClass_ wndClass_;

        return wndClass_.m_hInst_;
    }

    auto Window::WndClass_::GetName() noexcept -> str_t
    {
        return s_wndClassName_;
    }
}