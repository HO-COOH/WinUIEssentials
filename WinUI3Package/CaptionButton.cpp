#include "pch.h"
#include "CaptionButton.h"

bool CaptionButton::IsEnabled(HWND hwnd) const
{
    auto const style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    switch (m_value)
    {
        case CaptionButton::Minimize:   return (style & WS_MINIMIZEBOX) != 0;
        case CaptionButton::Maximize:   return (style & WS_MAXIMIZEBOX) != 0;
        case CaptionButton::Close:      return true;
        default:                        return false;
    }
}
