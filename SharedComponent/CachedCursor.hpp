#pragma once

#if defined Build_WinUIPackage
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
#else
template<typename Derived>
class CachedCursor
{
    winrt::Windows::UI::Core::CoreCursorType m_currentCursor{winrt::Windows::UI::Core::CoreCursorType::Arrow };
    winrt::Windows::UI::Core::CoreWindow m_coreWindow{ winrt::Windows::UI::Xaml::Window::Current().CoreWindow() };
protected:
    void setCursor(winrt::Windows::UI::Core::CoreCursorType cursorType)
    {
        if (m_currentCursor != cursorType)
        {
            m_currentCursor = cursorType;
            m_coreWindow.PointerCursor(winrt::Windows::UI::Core::CoreCursor(cursorType, 0));
        }
    }

    void resetCursor()
    {
        m_currentCursor = winrt::Windows::UI::Core::CoreCursorType::Arrow;
        m_coreWindow.PointerCursor(winrt::Windows::UI::Core::CoreCursor(winrt::Windows::UI::Core::CoreCursorType::Arrow, 0));
    }
};
#endif