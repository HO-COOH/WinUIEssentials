#include "pch.h"
#include "SettingsCommandEx.h"
#if __has_include("SettingsCommandEx.g.cpp")
#include "SettingsCommandEx.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::Foundation::IInspectable SettingsCommandEx::Id()
	{
		return m_id;
	}
	void SettingsCommandEx::Id(winrt::Windows::Foundation::IInspectable value)
	{
		m_id = value;
	}
	winrt::hstring SettingsCommandEx::Label()
	{
		return m_label;
	}
	void SettingsCommandEx::Label(winrt::hstring value)
	{
		m_label = value;
	}
	winrt::event_token SettingsCommandEx::Invoke(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Popups::IUICommand> const handler)
	{
		return m_InvokeEvent.add(handler);
	}
	void SettingsCommandEx::Invoke(winrt::event_token const& token) noexcept
	{
		m_InvokeEvent.remove(token);
	}
	winrt::Windows::UI::Popups::UICommandInvokedHandler SettingsCommandEx::Invoked()
	{
		return m_invokeHandler;
	}
	void SettingsCommandEx::Invoked(winrt::Windows::UI::Popups::UICommandInvokedHandler)
	{
	}
}
