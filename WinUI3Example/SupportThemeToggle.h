#pragma once

template<typename DerivedWindow>
class SupportThemeToggle
{
	constexpr auto& getSelf()
	{
		return *static_cast<DerivedWindow*>(this);
	}

	int m_themeIndex = 2;

public:
	void ThemeButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		m_themeIndex = (m_themeIndex + 1) % 3;
		auto boxedValue = getSelf().ThemeSwitcher().SwitchCases().GetAt(m_themeIndex).as<winrt::WinUI3Package::Case>().Value();
		getSelf().RootGrid().RequestedTheme(winrt::unbox_value<winrt::Microsoft::UI::Xaml::ElementTheme>(boxedValue));
		getSelf().ThemeSwitcher().Value(boxedValue);
	}
};
 