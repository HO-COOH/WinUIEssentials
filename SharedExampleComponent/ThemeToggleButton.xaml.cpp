#include "pch.h"
#include "ThemeToggleButton.xaml.h"
#if __has_include("ThemeToggleButton.g.cpp")
#include "ThemeToggleButton.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::PackageRoot::implementation
{
	ThemeToggleButton::ThemeToggleButton()
	{
		DefaultStyleKey(winrt::box_value(winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Controls::Button>()));
	}

	winrt::WinUINamespace::UI::Xaml::FrameworkElement ThemeToggleButton::Root()
	{
		return m_root;
	}

	void ThemeToggleButton::Root(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& value)
	{
		m_root = value;
	}

	void ThemeToggleButton::Button_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
		m_themeIndex = (m_themeIndex + 1) % 3;
#if defined Build_WinUIExample
		auto boxedValue = ThemeSwitcher().SwitchCases().GetAt(m_themeIndex).as<winrt::WinUI3Package::Case>().Value();
#else
		auto boxedValue = ThemeSwitcher().SwitchCases().GetAt(m_themeIndex).as<winrt::UWPPackage::Case>().Value();
#endif
		if (m_root)
			m_root.RequestedTheme(winrt::unbox_value<winrt::WinUINamespace::UI::Xaml::ElementTheme>(boxedValue));
		ThemeSwitcher().Value(boxedValue);
	}
}

