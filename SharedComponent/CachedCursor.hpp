#pragma once

template<typename Derived>
class CachedCursor
{
	winrt::Microsoft::UI::Input::InputSystemCursorShape m_currentCursor{ winrt::Microsoft::UI::Input::InputSystemCursorShape::Arrow };
protected:
    void setCursor(winrt::Microsoft::UI::Input::InputSystemCursorShape cursorShape)
    {
        if (m_currentCursor != cursorShape)
        {
            m_currentCursor = cursorShape;
            static_cast<Derived*>(this)->ProtectedCursor(winrt::Microsoft::UI::Input::InputSystemCursor::Create(cursorShape));
        }
    }

    void resetCursor()
    {
        m_currentCursor = winrt::Microsoft::UI::Input::InputSystemCursorShape::Arrow;
        static_cast<Derived*>(this)->ProtectedCursor(nullptr);
    }
};