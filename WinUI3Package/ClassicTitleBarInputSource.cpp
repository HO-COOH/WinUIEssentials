#include "pch.h"
#include "ClassicTitleBarInputSource.h"
#include <CommCtrl.h>
#include <dwmapi.h>
#include "ModernWindowCaptionButtonToolTip.h"
#pragma comment(lib, "dwmapi.lib")

//Class atom of the system caption button tooltip, a single window owned by csrss and shared by the whole desktop
constexpr static ATOM SystemToolTipClassAtom = 32774;

ClassicTitleBarInputSource::ClassicTitleBarInputSource(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND window)
    : InputSourceBase{ owner, window }
{
    if (m_hwnd)
        SetWindowSubclass(window, &subclassProc, SubclassId, reinterpret_cast<DWORD_PTR>(this));
}

ClassicTitleBarInputSource::~ClassicTitleBarInputSource()
{
    if (m_hwnd && IsWindow(m_hwnd))
        RemoveWindowSubclass(m_hwnd, &subclassProc, SubclassId);
}

LRESULT ClassicTitleBarInputSource::onSubclassMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    try
    {
        switch (msg)
        {
            case WM_NCMOUSEMOVE:
            {
                auto const button = CaptionButton::FromHitTest(wparam);
                if (button == CaptionButton::None)
                    m_systemToolTipHook.reset();
                else
                    installSystemToolTipHook();
                m_captionButtonTooltip.SetHoveredButton(button);
                break;
            }

            case WM_NCLBUTTONDOWN:
            case WM_NCLBUTTONDBLCLK:
            case WM_NCRBUTTONDOWN:
            case WM_NCRBUTTONDBLCLK:
            case WM_NCMBUTTONDOWN:
            case WM_NCMBUTTONDBLCLK:
            case WM_NCXBUTTONDOWN:
            case WM_NCXBUTTONDBLCLK:
                onPointerPressed();
                break;

            case WM_NCMOUSELEAVE:
                //Leave notifications are only a hint, the cursor position decides whether the button is still hovered
                if (!isPointerOver())
                {
                    m_systemToolTipHook.reset();
                    m_captionButtonTooltip.SetHoveredButton(CaptionButton::None);
                }
                break;

            case WM_NCDESTROY:
                RemoveWindowSubclass(hwnd, &subclassProc, SubclassId);
                m_hwnd = nullptr;
                m_systemToolTipHook.reset();
                m_captionButtonTooltip.SetHoveredButton(CaptionButton::None);
                break;
        }
    }
    catch (...)
    {
    }

    return DefSubclassProc(hwnd, msg, wparam, lparam);
}

LRESULT ClassicTitleBarInputSource::subclassProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    if (uIdSubclass != SubclassId)
        return DefSubclassProc(hwnd, msg, wparam, lparam);

    return reinterpret_cast<ClassicTitleBarInputSource*>(dwRefData)->onSubclassMessage(hwnd, msg, wparam, lparam);
}

void ClassicTitleBarInputSource::installSystemToolTipHook()
{
    if (m_systemToolTipHook)
        return;

    //Only listen to the thread of the system tooltip, or every window when it is not found
    DWORD processId{};
    DWORD threadId{};
    if (auto const tooltip = FindWindowExW(nullptr, nullptr, MAKEINTATOM(SystemToolTipClassAtom), nullptr))
        threadId = GetWindowThreadProcessId(tooltip, &processId);

    m_systemToolTipHook.reset(SetWinEventHook(
        EVENT_OBJECT_SHOW,
        EVENT_OBJECT_SHOW,
        nullptr,
        &onSystemToolTipShown,
        processId,
        threadId,
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
    ));
}

void ClassicTitleBarInputSource::onSystemToolTipShown(HWINEVENTHOOK, DWORD, HWND hwnd, LONG idObject, LONG, DWORD, DWORD)
{
    if (idObject != OBJID_WINDOW || GetClassWord(hwnd, GCW_ATOM) != SystemToolTipClassAtom)
        return;

    //The tooltip is shared by every window, only hide it for the caption buttons of a window we handle
    POINT cursor{};
    if (!GetCursorPos(&cursor))
        return;

    auto const window = WindowFromPoint(cursor);
    if (!window || GetWindowThreadProcessId(window, nullptr) != GetCurrentThreadId() || !GetWindowSubclass(window, &subclassProc, SubclassId, nullptr))
        return;

    SetWindowPos(
        hwnd, 
        nullptr, 
        0, 0, 0, 0, 
        SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE
    );
}

LONG ClassicTitleBarInputSource::CaptionTop(LONG fallback) const
{
    //The window rect also has the invisible resize borders above the caption
    RECT rect{ .top = fallback };
    if (m_hwnd)
        DwmGetWindowAttribute(m_hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(rect));
    return rect.top;
}
