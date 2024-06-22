#include "pch.h"
#include "SettingsExpanderItemStyleSelector.h"
#if __has_include("SettingsExpanderItemStyleSelector.g.cpp")
#include "SettingsExpanderItemStyleSelector.g.cpp"
#endif
#include "SettingsCard.g.h"

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::Style SettingsExpanderItemStyleSelector::DefaultStyle()
	{
		return m_defaultStyle;
	}
	void SettingsExpanderItemStyleSelector::DefaultStyle(winrt::Windows::UI::Xaml::Style value)
	{
		m_defaultStyle = value;
	}
	winrt::Windows::UI::Xaml::Style SettingsExpanderItemStyleSelector::ClickableStyle()
	{
		return m_clickableStyle;
	}
	void SettingsExpanderItemStyleSelector::ClickableStyle(winrt::Windows::UI::Xaml::Style value)
	{
		m_clickableStyle = value;
	}
	winrt::Windows::UI::Xaml::Style SettingsExpanderItemStyleSelector::SelectStyleCore(
		winrt::Windows::Foundation::IInspectable item,
		winrt::Windows::UI::Xaml::DependencyObject container)
	{
		if (auto card = container.try_as<winrt::UWPPackage::SettingsCard>(); card && card.IsClickEnabled())
			return m_clickableStyle;
		return m_defaultStyle;
	}
}
