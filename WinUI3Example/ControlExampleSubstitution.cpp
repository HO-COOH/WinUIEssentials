#include "pch.h"
#include "ControlExampleSubstitution.h"
#if __has_include("ControlExampleSubstitution.g.cpp")
#include "ControlExampleSubstitution.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
    winrt::hstring ControlExampleSubstitution::Key()
    {
        return m_key;
    }
    void ControlExampleSubstitution::Key(winrt::hstring const& value)
    {
        m_key = value;
    }
    winrt::hstring ControlExampleSubstitution::Value()
    {
        return m_value;
    }
    void ControlExampleSubstitution::Value(winrt::hstring const& value)
    {
		m_value = value;
        if (ValueChanged)
            ValueChanged();
    }
    bool ControlExampleSubstitution::IsEnabled()
    {
        return m_isEnabled;
    }
    void ControlExampleSubstitution::IsEnabled(bool value)
    {
		m_isEnabled = value;
    }
}
