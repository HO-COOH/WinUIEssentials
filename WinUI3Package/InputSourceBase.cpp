#include "pch.h"
#include "InputSourceBase.hpp"
#include "ModernWindowCaptionButtonToolTip.h"

InputSourceBase::InputSourceBase(winrt::WinUI3Package::implementation::ModernWindowCaptionButtonToolTip& owner, HWND window) :
    m_captionButtonTooltip{ owner },
    m_hwnd{ window }
{
}

bool InputSourceBase::isPointerOver() const
{
    POINT cursor{};
    if (!GetCursorPos(&cursor))
        return false;
    return WindowFromPoint(cursor) == m_hwnd;
}

void InputSourceBase::onPointerPressed()
{
    m_captionButtonTooltip.CloseToolTip();
    m_captionButtonTooltip.m_isSuppressedUntilButtonChanges = true;
}
