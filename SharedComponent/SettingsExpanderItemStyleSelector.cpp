#include "pch.h"
#include "SettingsExpanderItemStyleSelector.h"
#if __has_include("SettingsExpanderItemStyleSelector.g.cpp")
#include "SettingsExpanderItemStyleSelector.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	winrt::WinUINamespace::UI::Xaml::Style SettingsExpanderItemStyleSelector::DefaultStyle()
	{
		return m_defaultStyle;
	}
	void SettingsExpanderItemStyleSelector::DefaultStyle(winrt::WinUINamespace::UI::Xaml::Style const& value)
	{
		m_defaultStyle = value;
	}
	winrt::WinUINamespace::UI::Xaml::Style SettingsExpanderItemStyleSelector::ClickableStyle()
	{
		return m_clickableStyle;
	}
	void SettingsExpanderItemStyleSelector::ClickableStyle(winrt::WinUINamespace::UI::Xaml::Style const& value)
	{
		m_clickableStyle = value;
	}
	winrt::WinUINamespace::UI::Xaml::Style SettingsExpanderItemStyleSelector::SelectStyleCore(
		winrt::Windows::Foundation::IInspectable const& item,
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& container)
	{
		if (auto card = container.try_as<winrt::PackageRoot::SettingsCard>(); card && card.IsClickEnabled())
			return m_clickableStyle;
		return m_defaultStyle;
	}
}
