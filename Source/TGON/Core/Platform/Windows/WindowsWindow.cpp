#include "PrecompiledHeader.h"
#include "WindowsWindow.h"

#include "WindowsWindowUtility.h"
#include "WindowsApplication.h"
#include "Core/String/TEncoding.h"

#include <Windows.h>
#include <cassert>

#ifdef TGON_SUPPORT_DWMAPI
#   include <dwmapi.h>
#   pragma comment(lib, "dwmapi.lib")
#endif

namespace tgon {
namespace platform {

WindowsWindow::WindowsWindow(const WindowStyle& wndStyle) :
    m_wndHandle(CreateWindowForm(wndStyle, L"TGON", platform::windows::GetInstanceHandle()))
{
    assert(m_wndHandle != nullptr && "Failed to create window.");

    // Save this instance's pointer to storage of window.
    SetWindowLongPtrW(m_wndHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

WindowsWindow::~WindowsWindow()
{
    DestroyWindow(m_wndHandle);
}

bool WindowsWindow::PumpEvent()
{
    MSG msg {0};
    if (PeekMessageW(&msg, m_wndHandle, 0, 0, PM_REMOVE) == TRUE)
    {
        ::DispatchMessageW(&msg);
        return true;
    }
    else
    {
        return false;
    }
}

void WindowsWindow::BringToFront()
{
    // After Windows 98/Me: The system restricts which processes can set the foreground window.
    // So, you can't switch the focus freely by only SetFocus or SetForegroundWindow.

    DWORD currProcessId = GetWindowThreadProcessId(m_wndHandle, nullptr);
    DWORD foregroundProcessId = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);

    if (AttachThreadInput(currProcessId, foregroundProcessId, TRUE))
    {
        SetForegroundWindow(m_wndHandle);
        BringWindowToTop(m_wndHandle);

        AttachThreadInput(currProcessId, foregroundProcessId, TRUE);
    }
}

void WindowsWindow::Flash()
{
    FLASHWINFO fwi{ 0 };
    fwi.cbSize = sizeof(FLASHWINFO);
    fwi.dwFlags = FLASHW_CAPTION;
    fwi.dwTimeout = 0;
    fwi.hwnd = m_wndHandle;
    fwi.uCount = 1;

    FlashWindowEx(&fwi);
}

const math::TIntPoint WindowsWindow::GetPosition() const
{
    RECT rt;
    ::GetWindowRect(m_wndHandle, &rt);

    return {rt.left, rt.top};
}

const math::TIntExtent WindowsWindow::GetExtent() const
{
    RECT rt;
    ::GetClientRect(m_wndHandle, &rt);

    return {rt.right, rt.bottom};
}

void WindowsWindow::GetCaptionText(char* dest) const
{
    //virtual void GetCaptionText(char* caption) const override;
    //std::size_t captionTextLength = GetWindowTextLengthW(m_wndHandle);
    
    //::GetWindowTextW(m_wndHandle, dest, captionTextLength);
}

HWND WindowsWindow::GetWindowHandle() const noexcept
{
	return m_wndHandle;
}

bool WindowsWindow::HasThickframe() const
{
    // Todo: �׽�Ʈ �ʿ�

    DWORD style = ::GetWindowLongPtrW(m_wndHandle, GWL_STYLE);
    DWORD extendedStyle = ::GetWindowLongPtrW(m_wndHandle, GWL_EXSTYLE);

    return ((style & WS_THICKFRAME) != 0) || ((extendedStyle & WS_EX_DLGMODALFRAME) != 0);
}

void WindowsWindow::Show()
{
    ::ShowWindow(m_wndHandle, SW_NORMAL);
}

void WindowsWindow::Hide()
{
    ::ShowWindow(m_wndHandle, SW_HIDE);
}

void WindowsWindow::Maximize()
{
    ::ShowWindow(m_wndHandle, SW_MAXIMIZE);
}

void WindowsWindow::Minimize()
{
    ::ShowWindow(m_wndHandle, SW_MINIMIZE);
}

void WindowsWindow::Quit()
{
    ::PostQuitMessage(0);
}

void WindowsWindow::SetPosition(const math::TIntPoint& position)
{
    ::SetWindowPos(m_wndHandle, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE);
}

void WindowsWindow::SetExtent(const math::TIntExtent& extent)
{
    ::SetWindowPos(m_wndHandle, nullptr, 0, 0, extent.width, extent.height, SWP_NOMOVE);
}

void WindowsWindow::SetCaption(const char* caption)
{
    wchar_t utf16Caption[256] {};

    bool succeed = string::ConvertUTF8ToUTF16(caption, reinterpret_cast<char*>(utf16Caption)) != -1;
    if (succeed)
    {
        ::SetWindowTextW(m_wndHandle, utf16Caption);
    }
}

void WindowsWindow::SetTopMost(bool setTopMost)
{
    ::SetWindowPos(m_wndHandle, setTopMost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

//void WindowsWindow::AdditionalInit(const WindowStyle& wndStyle)
//{
//    if (wndStyle.supportWindowTransparency)
//    {
//        SetLayeredWindowAttributes(m_wndHandle, NULL, 255, LWA_ALPHA);
//    }
//
//#ifdef TGON_SUPPORT_DWMAPI
//    if (wndStyle.supportPerPixelTransparency)
//    {
//        BOOL isCompoEnabled = FALSE;
//        DwmIsCompositionEnabled(&isCompoEnabled);
//
//        if (isCompoEnabled == TRUE)
//        {
//            MARGINS margins{ -1, -1, -1, -1 };
//            DwmExtendFrameIntoClientArea(m_wndHandle, &margins);
//        }
//    }
//#endif
//}

LRESULT WindowsWindow::OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        /* WARN: DO NOT HANDLE THIS MESSAGE */
        break;

    case WM_SETFOCUS:
        {
            this->OnGetFocus();
        }
        break;

    case WM_KILLFOCUS:
        {
            this->OnLoseFocus();
        }
        break;

    case WM_MOVE:
        {
            this->OnMove({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)});
        }
        break;

    case WM_SIZE:
        {
            this->OnResizeExtent({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)});
        }
        break;

    case WM_DESTROY:
        {
            PostQuitMessage(0);
            m_isClosed = true;
        }
        break;

    case WM_LBUTTONDOWN:
        {
            this->OnMouseDown({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Left);
        }
        break;

    case WM_LBUTTONUP:
        {
            this->OnMouseUp({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Left);
        }
        break;

    case WM_RBUTTONDOWN:
        {
            this->OnMouseDown({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Right);
        }
        break;

    case WM_RBUTTONUP:
        {
            this->OnMouseUp({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Right);
        }
        break;

    case WM_MBUTTONDOWN:
        {
            this->OnMouseDown({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Middle);
        }
        break;

    case WM_MBUTTONUP:
        {
            this->OnMouseUp({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Middle);
        }
        break;

    case WM_LBUTTONDBLCLK:
        {
            this->OnMouseDoubleClick({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Left);
        }
        break;

    case WM_RBUTTONDBLCLK:
        {
            this->OnMouseDoubleClick({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Right);
        }
        break;

    case WM_MBUTTONDBLCLK:
        {
            this->OnMouseDoubleClick({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)}, MouseType::Middle);
        }
        break;

    case WM_MOUSEMOVE:
        {
            this->OnMouseMove({(std::size_t)LOWORD(lParam), (std::size_t)HIWORD(lParam)});
        }
        break;
    }

    return DefWindowProc(wndHandle, msg, wParam, lParam);
}

} /* namespace platform */
} /* namespace tgon */