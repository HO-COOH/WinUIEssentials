#include "pch.h"
#include "InputNonClientPointerSource.h"
#include <CommCtrl.h>
#include "ModernWindowCaptionButtonToolTip.h"

static bool isMouseButtonDown()
{
    return ((GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) | GetAsyncKeyState(VK_MBUTTON)) & 0x8000) != 0;
}

bool InputNonClientPointerSource::isNonClientInputSink(HWND hwnd)
{
    constexpr static std::wstring_view NonClientInputSinkClassName{ L"InputNonClientPointerSource" };

    wchar_t className[NonClientInputSinkClassName.size() + 1]{};
    GetClassNameW(hwnd, className, static_cast<int>(std::size(className)));
    return NonClientInputSinkClassName == className;
}

//win32k only shows the system Minimize/Maximize tooltips when the hit-test window has these styles
constexpr static DWORD CaptionButtonStylesToRemove = WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

//win32k always shows the system tooltip for HTCLOSE, but never for HTBORDER
constexpr static LRESULT CloseButtonSubstituteHitTest = HTBORDER;

InputNonClientPointerSource::InputNonClientPointerSource(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND sink)
    : InputSourceBase{ owner, sink }
{
    if (sink && SetWindowSubclass(sink, &nonClientInputSinkSubclassProc, SubclassId, reinterpret_cast<DWORD_PTR>(this)))
        disableMinimizeAndMaximizeTooltipByStyle();
}

InputNonClientPointerSource::~InputNonClientPointerSource()
{
    detach();
}

HWND InputNonClientPointerSource::Find(HWND window)
{
    //EnumChildWindows would enumerate the top-level windows instead
    if (!window)
        return nullptr;

    struct Search
    {
        DWORD threadId;
        HWND result;
    } search{ GetCurrentThreadId(), nullptr };

    EnumChildWindows(
        window,
        [](HWND child, LPARAM lparam) -> BOOL
        {
            auto& search = *reinterpret_cast<Search*>(lparam);
            if (GetWindowThreadProcessId(child, nullptr) == search.threadId && isNonClientInputSink(child))
            {
                search.result = child;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&search)
    );

    //Not IsWindowVisible, which is also false while the window has not shown yet
    auto const sink = search.result;
    return sink && (GetWindowLongPtrW(sink, GWL_STYLE) & WS_VISIBLE) ? sink : nullptr;
}

LRESULT InputNonClientPointerSource::onSubclassMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    //In each case, restore the hit-test value / clean up before anything that can throw,
    //so the message is still forwarded correctly if the tooltip logic fails
    try
    {
        switch (msg)
        {
            case WM_NCHITTEST:
            {
                auto const hitTest = DefSubclassProc(hwnd, msg, wparam, lparam);
                m_lastHitTest = hitTest;
                if (hitTest == HTCLOSE && !isPressed())
                    return CloseButtonSubstituteHitTest;
                return hitTest;
            }

            case WM_STYLECHANGING:
                if (wparam == GWL_STYLE && !m_isSettingStyle)
                {
                    auto& styles = *reinterpret_cast<STYLESTRUCT*>(lparam);
                    m_strippedStyle = std::exchange(styles.styleNew, styles.styleNew & ~CaptionButtonStylesToRemove) & CaptionButtonStylesToRemove;
                }
                break;

                //The system computed the hit-test values in these messages from HTBORDER for the close button
            case WM_NCMOUSEMOVE:
                wparam = restoreHitTest(wparam);
                m_captionButtonTooltip.SetHoveredButton(CaptionButton::FromHitTest(wparam));
                break;

            case WM_NCMOUSEHOVER:
            case WM_NCLBUTTONUP:
            case WM_NCRBUTTONUP:
            case WM_NCMBUTTONUP:
                wparam = restoreHitTest(wparam);
                break;

            case WM_NCLBUTTONDOWN:
            case WM_NCLBUTTONDBLCLK:
            case WM_NCRBUTTONDOWN:
            case WM_NCRBUTTONDBLCLK:
            case WM_NCMBUTTONDOWN:
            case WM_NCMBUTTONDBLCLK:
                wparam = restoreHitTest(wparam);
                onPointerPressed();
                break;

            case WM_NCXBUTTONUP:
                wparam = MAKEWPARAM(restoreHitTest(LOWORD(wparam)), HIWORD(wparam));
                break;

            case WM_NCXBUTTONDOWN:
            case WM_NCXBUTTONDBLCLK:
                wparam = MAKEWPARAM(restoreHitTest(LOWORD(wparam)), HIWORD(wparam));
                onPointerPressed();
                break;

            case WM_SETCURSOR:
            case WM_MOUSEACTIVATE:
                lparam = MAKELPARAM(restoreHitTest(LOWORD(lparam)), HIWORD(lparam));
                break;

                //HIWORD(wparam) of the WM_NCPOINTER* messages holds pointer flags, not a hit-test code
            case WM_NCPOINTERUPDATE:
                if (IS_POINTER_INCONTACT_WPARAM(wparam))
                    onPointerPressed(GET_POINTERID_WPARAM(wparam));
                else
                    m_captionButtonTooltip.SetHoveredButton(CaptionButton::FromHitTest(m_lastHitTest));
                break;

            case WM_NCPOINTERDOWN:
            case WM_POINTERDOWN:
                onPointerPressed(GET_POINTERID_WPARAM(wparam));
                break;

            case WM_NCPOINTERUP:
            case WM_POINTERUP:
            case WM_POINTERCAPTURECHANGED:
                m_pressedPointerId.reset();
                break;

            case WM_LBUTTONDOWN:
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_XBUTTONDOWN:
                onPointerPressed();
                break;

            case WM_NCMOUSELEAVE:
            case WM_MOUSELEAVE:
            case WM_POINTERLEAVE:
                //Leave notifications are only a hint, the cursor position decides whether the button is still hovered
                if (!isPointerOver())
                    m_captionButtonTooltip.SetHoveredButton(CaptionButton::None);
                break;

            case WM_NCDESTROY:
                RemoveWindowSubclass(hwnd, &nonClientInputSinkSubclassProc, SubclassId);
                m_hwnd = nullptr;
                m_strippedStyle = 0;
                m_lastHitTest = HTNOWHERE;
                m_pressedPointerId.reset();
                m_captionButtonTooltip.SetHoveredButton(CaptionButton::None);
                break;
        }
    }
    catch (...)
    {
    }

    return DefSubclassProc(hwnd, msg, wparam, lparam);
}

LRESULT InputNonClientPointerSource::nonClientInputSinkSubclassProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    if (uIdSubclass != SubclassId)
        return DefSubclassProc(hwnd, msg, wparam, lparam);

	return reinterpret_cast<InputNonClientPointerSource*>(dwRefData)->onSubclassMessage(hwnd, msg, wparam, lparam);
}

void InputNonClientPointerSource::onPointerPressed(UINT32 pointerId)
{
    m_pressedPointerId = pointerId;
    onPointerPressed();
}

bool InputNonClientPointerSource::isPressed()
{
    if (isMouseButtonDown())
        return true;

    //for pen and touch
    if (m_pressedPointerId)
    {
        POINTER_INFO info{};
        if (GetPointerInfo(*m_pressedPointerId, &info) && (info.pointerFlags & POINTER_FLAG_INCONTACT))
            return true;
        m_pressedPointerId.reset();
    }
    return false;
}

void InputNonClientPointerSource::detach()
{
	m_lastHitTest = HTNOWHERE;
    auto const oldSink = std::exchange(m_hwnd, nullptr);
    auto const oldStyle = std::exchange(m_strippedStyle, 0);
    if (!oldSink || !IsWindow(oldSink))
        return;

    RemoveWindowSubclass(oldSink, &nonClientInputSinkSubclassProc, SubclassId);
    if (oldStyle)
        SetWindowLongPtrW(oldSink, GWL_STYLE, GetWindowLongPtrW(oldSink, GWL_STYLE) | oldStyle);
}

LRESULT InputNonClientPointerSource::restoreHitTest(LRESULT hitTest) const
{
    return hitTest == CloseButtonSubstituteHitTest && m_lastHitTest == HTCLOSE ? HTCLOSE : hitTest;
}


void InputNonClientPointerSource::disableMinimizeAndMaximizeTooltipByStyle()
{
    auto const style = GetWindowLongPtrW(m_hwnd, GWL_STYLE);
    if (m_strippedStyle = (style & CaptionButtonStylesToRemove)) //remove these two styles so that windows does not show the default tooltip
    {
        m_isSettingStyle = true;
        SetWindowLongPtrW(m_hwnd, GWL_STYLE, style & ~CaptionButtonStylesToRemove);
        m_isSettingStyle = false;
    }
}

LONG InputNonClientPointerSource::CaptionTop(LONG fallback) const
{
    RECT rect{ .top = fallback };
    if (m_hwnd)
        GetWindowRect(m_hwnd, &rect);
    return rect.top;
}
