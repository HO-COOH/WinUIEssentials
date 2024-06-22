#include "pch.h"
#include "SettingsExpanderItemStyleSelector.h"
#if __has_include("SettingsExpanderItemStyleSelector.g.cpp")
#include "SettingsExpanderItemStyleSelector.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::Style SettingsExpanderItemStyleSelector::DefaultStyle()
	{
		return m_defaultStyle;
	}
	void SettingsExpanderItemStyleSelector::DefaultStyle(winrt::Microsoft::UI::Xaml::Style value)
	{
		m_defaultStyle = value;
	}
	winrt::Microsoft::UI::Xaml::Style SettingsExpanderItemStyleSelector::ClickableStyle()
	{
		return m_clickableStyle;
	}
	void SettingsExpanderItemStyleSelector::ClickableStyle(winrt::Microsoft::UI::Xaml::Style value)
	{
		m_clickableStyle = value;
	}
	winrt::Microsoft::UI::Xaml::Style SettingsExpanderItemStyleSelector::SelectStyleCore(
		winrt::Windows::Foundation::IInspectable item,
		winrt::Microsoft::UI::Xaml::DependencyObject container)
	{
		if (auto card = container.try_as<winrt::WinUI3Package::SettingsCard>(); card && card.IsClickEnabled())
			return m_clickableStyle;
		return m_defaultStyle;
	}
}
